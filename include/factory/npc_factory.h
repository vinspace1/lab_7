#pragma once


#include <memory>
#include <string>
#include <random>
#include "../npc/npc.h"

class NPCFactory {
private:
    static std::mt19937 randomGen;
    static std::uniform_int_distribution<int> posDist;
    static std::uniform_int_distribution<int> typeDist;
    
public:
    static void initRandom();
    
    static std::shared_ptr<NPC> createNPC(
        NpcType type, 
        int x, 
        int y, 
        const std::string& name
    );
    
    static std::shared_ptr<NPC> createRandomNPC();
    static std::string getRandomName(NpcType type);
    
    static std::shared_ptr<NPC> createNPCFromString(const std::string& data);
    static std::string serializeNPC(const std::shared_ptr<NPC>& npc);
    
    // Таблица параметров для NPC
    static int getMoveDistance(NpcType type);
    static int getKillDistance(NpcType type);
};