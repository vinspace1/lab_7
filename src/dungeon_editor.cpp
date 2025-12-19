#include "../include/dungeon_editor.h"
#include "../include/factory/npc_factory.h"
#include "../include/visitor/battle_visitor.h"
#include "../include/game/game_constants.h"
#include "../include/factory/visitor_factory.h"
#include <iostream>
#include <chrono>
#include <thread>

DungeonEditor::DungeonEditor() 
    : gameMap(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT),
      running(false), gameOver(false) {
    NPC::initRandom();
    NPCFactory::initRandom();
}

DungeonEditor::~DungeonEditor() {
    stopGame();
}

void DungeonEditor::startGame() {
    if (running) return;
    
    running = true;
    gameOver = false;
    startTime = std::chrono::steady_clock::now();
    
    initializeGame();
    
    // Запускаем потоки
    moveThread = std::thread(&DungeonEditor::moveNPCsThread, this);
    battleThread = std::thread(&DungeonEditor::processBattlesThread, this);
    printThread = std::thread(&DungeonEditor::printMapThread, this);
    
    // Запускаем главный игровой цикл
    runGameLoop();
}

void DungeonEditor::stopGame() {
    running = false;
    gameOver = true;
    
    // Уведомляем все потоки
    battleCV.notify_all();
    
    // Ждем завершения потоков
    if (moveThread.joinable()) moveThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printThread.joinable()) printThread.join();
}

void DungeonEditor::runGameLoop() {
    auto start = std::chrono::steady_clock::now();
    
    while (running && !gameOver) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        
        if (elapsed >= GameConstants::GAME_DURATION) {
            gameOver = true;
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    // Игра окончена
    stopGame();
    
    // Печатаем выживших
    printSurvivors();
}

void DungeonEditor::moveNPCsThread() {
    while (running) {
        // Двигаем NPC
        gameMap.moveAllNPCs();
        
        // Обнаруживаем битвы
        auto battles = gameMap.detectBattles();
        for (const auto& [attacker, defender] : battles) {
            addBattleToQueue(attacker, defender);
        }
        
        std::this_thread::sleep_for(
            std::chrono::milliseconds(GameConstants::MOVE_UPDATE_MS));
    }
}

void DungeonEditor::processBattlesThread() {
    while (running) {
        std::unique_lock lock(battleQueueMutex);
        
        // Ждем битв в очереди
        battleCV.wait_for(lock, 
            std::chrono::milliseconds(GameConstants::BATTLE_UPDATE_MS),
            [this]() { return !battleQueue.empty() || !running; });
        
        // Обрабатываем все битвы в очереди
        while (!battleQueue.empty()) {
            auto [attacker, defender] = battleQueue.front();
            battleQueue.pop();
            
            lock.unlock();
            processBattle(attacker, defender);
            lock.lock();
        }
    }
}

void DungeonEditor::printMapThread() {
    while (running) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(GameConstants::PRINT_UPDATE_MS));
        
        if (running) {
            gameMap.printMap();
        }
    }
}

void DungeonEditor::addBattleToQueue(const std::shared_ptr<NPC>& attacker, 
                                    const std::shared_ptr<NPC>& defender) {
    std::lock_guard lock(battleQueueMutex);
    battleQueue.emplace(attacker, defender);
    battleCV.notify_one();
}

void DungeonEditor::processBattle(const std::shared_ptr<NPC>& attacker, 
                                 const std::shared_ptr<NPC>& defender) {
    if (!attacker->isAlive() || !defender->isAlive()) {
        return;
    }
    
    // Проверяем правила битвы через Visitor
    auto attackerVisitor = VisitorFactory::createVisitor(attacker);
    auto defenderVisitor = VisitorFactory::createVisitor(defender);
    
    // Используем кубики
    bool attackerWins = attacker->fight(defender);
    
    if (attackerWins) {
        defender->kill();
        notifyObservers(attacker, defender, true);
        safePrint(attacker->getName() + " kills " + defender->getName() + "!");
    } else {
        safePrint(attacker->getName() + " fails to kill " + defender->getName());
    }
    
    // Удаляем мертвых NPC
    gameMap.removeDeadNPCs();
}

void DungeonEditor::initializeGame() {
    safePrint("Initializing game with " + 
              std::to_string(GameConstants::INITIAL_NPC_COUNT) + " NPCs");
    
    gameMap.generateRandomNPCs(GameConstants::INITIAL_NPC_COUNT);
    
    safePrint("Game started! Duration: " + 
              std::to_string(GameConstants::GAME_DURATION) + " seconds");
}

void DungeonEditor::cleanup() {
    gameMap.clear();
}

void DungeonEditor::addObserver(const std::shared_ptr<Observer>& observer) {
    std::lock_guard lock(observersMutex);
    observers.push_back(observer);
}

void DungeonEditor::removeObserver(const std::shared_ptr<Observer>& observer) {
    std::lock_guard lock(observersMutex);
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void DungeonEditor::notifyObservers(
    const std::shared_ptr<NPC>& attacker,
    const std::shared_ptr<NPC>& defender,
    bool defender_killed
) const {
    std::lock_guard lock(observersMutex);
    for (const auto& observer : observers) {
        observer->onFight(attacker, defender, defender_killed);
    }
}

void DungeonEditor::printSurvivors() const {
    safePrint("\n=== GAME OVER ===");
    safePrint("Survivors:");
    
    auto survivors = gameMap.getAliveNPCs();
    for (const auto& npc : survivors) {
        safePrint("  " + npc->toString());
    }
    
    safePrint("Total survivors: " + std::to_string(survivors.size()));
}

void DungeonEditor::safePrint(const std::string& message) const {
    std::lock_guard lock(coutMutex);
    std::cout << message << std::endl;
}