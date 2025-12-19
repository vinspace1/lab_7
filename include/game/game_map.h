#pragma once


#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include "../npc/npc.h"

class GameMap {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex;
    
    int width;
    int height;
    
public:
    GameMap(int width, int height);
    
    // Потокобезопасные операции
    void addNPC(const std::shared_ptr<NPC>& npc);
    void removeDeadNPCs();
    void clear();
    
    // Получение NPC
    std::vector<std::shared_ptr<NPC>> getAliveNPCs() const;
    std::vector<std::shared_ptr<NPC>> getAllNPCs() const;
    size_t getAliveCount() const;
    size_t getTotalCount() const;
    
    // Движение NPC
    void moveAllNPCs();
    
    // Обнаружение битв
    std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> 
    detectBattles() const;
    
    // Печать карты
    void printMap() const;
    
    // Генерация случайных NPC
    void generateRandomNPCs(size_t count);
    
private:
    char getCellChar(int x, int y) const;
    bool isPositionValid(int x, int y) const;
};