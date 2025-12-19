#include "../../include/game/game_map.h"
#include "../../include/factory/npc_factory.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

GameMap::GameMap(int width, int height) 
    : width(width), height(height) {
    NPCFactory::initRandom();
}

void GameMap::addNPC(const std::shared_ptr<NPC>& npc) {
    std::unique_lock lock(npcsMutex);
    npcs.push_back(npc);
}

void GameMap::removeDeadNPCs() {
    std::unique_lock lock(npcsMutex);
    auto it = std::remove_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) {
            return !npc->isAlive();
        });
    npcs.erase(it, npcs.end());
}

void GameMap::clear() {
    std::unique_lock lock(npcsMutex);
    npcs.clear();
}

std::vector<std::shared_ptr<NPC>> GameMap::getAliveNPCs() const {
    std::shared_lock lock(npcsMutex);
    std::vector<std::shared_ptr<NPC>> alive;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            alive.push_back(npc);
        }
    }
    
    return alive;
}

std::vector<std::shared_ptr<NPC>> GameMap::getAllNPCs() const {
    std::shared_lock lock(npcsMutex);
    return npcs;
}

size_t GameMap::getAliveCount() const {
    std::shared_lock lock(npcsMutex);
    size_t count = 0;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) count++;
    }
    
    return count;
}

size_t GameMap::getTotalCount() const {
    std::shared_lock lock(npcsMutex);
    return npcs.size();
}

void GameMap::moveAllNPCs() {
    auto aliveNPCs = getAliveNPCs();
    
    for (auto& npc : aliveNPCs) {
        npc->moveRandomly();
    }
}

std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> 
GameMap::detectBattles() const {
    std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battles;
    auto aliveNPCs = getAliveNPCs();
    
    for (size_t i = 0; i < aliveNPCs.size(); i++) {
        for (size_t j = i + 1; j < aliveNPCs.size(); j++) {
            auto& npc1 = aliveNPCs[i];
            auto& npc2 = aliveNPCs[j];
            
            double distance = npc1->distanceTo(npc2);
            
            // Проверяем, находятся ли NPC в зоне убийства друг друга
            if (distance <= npc1->getKillDistance() || 
                distance <= npc2->getKillDistance()) {
                battles.emplace_back(npc1, npc2);
            }
        }
    }
    
    return battles;
}

void GameMap::printMap() const {
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));
    
    // Собираем позиции живых NPC
    auto aliveNPCs = getAliveNPCs();
    for (const auto& npc : aliveNPCs) {
        int x = npc->getX();
        int y = npc->getY();
        
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = getCellChar(x, y);
        }
    }
    
    // Печатаем карту
    std::cout << "\n=== GAME MAP (" << aliveNPCs.size() << " alive NPCs) ===\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << "===========================\n" << std::endl;
}

void GameMap::generateRandomNPCs(size_t count) {
    std::unique_lock lock(npcsMutex);
    
    for (size_t i = 0; i < count; i++) {
        auto npc = NPCFactory::createRandomNPC();
        npcs.push_back(npc);
    }
}

char GameMap::getCellChar(int x, int y) const {
    // Ищем NPC в этой клетке
    auto aliveNPCs = getAliveNPCs();
    for (const auto& npc : aliveNPCs) {
        if (npc->getX() == x && npc->getY() == y) {
            // Возвращаем первую букву типа NPC
            switch (npc->getType()) {
                case NpcType::Orc: return 'O';
                case NpcType::Squirrel: return 'S';
                case NpcType::Druid: return 'D';
                case NpcType::Knight: return 'K';
                case NpcType::Elf: return 'E';
                case NpcType::Dragon: return 'R'; // Dragon -> R (чтобы не путать с Druid)
                case NpcType::Bear: return 'B';
                case NpcType::Robber: return 'R';
                case NpcType::Werewolf: return 'W';
                case NpcType::Princess: return 'P';
                case NpcType::Toad: return 'T';
                case NpcType::Slaver: return 'L';
                case NpcType::Pegasus: return 'G';
                case NpcType::Bittern: return 'I';
                case NpcType::Desman: return 'M';
                case NpcType::Bull: return 'U';
                default: return '?';
            }
        }
    }
    
    return '.'; // Пустая клетка
}

bool GameMap::isPositionValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}