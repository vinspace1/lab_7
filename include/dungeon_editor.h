#pragma once


#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include "npc/npc.h"
#include "observer/observer.h"
#include "game/game_map.h"

class DungeonEditor {
private:
    GameMap gameMap;
    std::vector<std::shared_ptr<Observer>> observers;
    mutable std::mutex observersMutex;
    mutable std::mutex coutMutex;  // Для синхронизации вывода в cout
    
    // Потоки
    std::thread moveThread;
    std::thread battleThread;
    std::thread printThread;
    
    // Атомарные флаги
    std::atomic<bool> running;
    std::atomic<bool> gameOver;
    
    // Очередь битв
    std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battleQueue;
    mutable std::mutex battleQueueMutex;
    std::condition_variable battleCV;
    
    // Таймер игры
    std::chrono::steady_clock::time_point startTime;
    
public:
    DungeonEditor();
    ~DungeonEditor();
    
    // Основные методы
    void startGame();
    void stopGame();
    void runGameLoop();
    
    // Потоковые функции
    void moveNPCsThread();
    void processBattlesThread();
    void printMapThread();
    
    // Обработка битв
    void addBattleToQueue(const std::shared_ptr<NPC>& attacker, 
                         const std::shared_ptr<NPC>& defender);
    void processBattle(const std::shared_ptr<NPC>& attacker, 
                      const std::shared_ptr<NPC>& defender);
    
    // Наблюдатели
    void addObserver(const std::shared_ptr<Observer>& observer);
    void removeObserver(const std::shared_ptr<Observer>& observer);
    void notifyObservers(
        const std::shared_ptr<NPC>& attacker,
        const std::shared_ptr<NPC>& defender,
        bool defender_killed
    ) const;
    
    // Утилиты
    void printSurvivors() const;
    void safePrint(const std::string& message) const;
    
    // Геттеры
    bool isRunning() const { return running.load(); }
    bool isGameOver() const { return gameOver.load(); }
    const GameMap& getGameMap() const { return gameMap; }
    
private:
    void initializeGame();
    void cleanup();
};