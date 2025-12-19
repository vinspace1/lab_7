#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../include/npc/orc.h"
#include "../include/npc/squirrel.h"
#include "../include/npc/druid.h"
#include "../include/npc/knight.h"
#include "../include/npc/elf.h"
#include "../include/npc/dragon.h"
#include "../include/npc/bear.h"
#include "../include/npc/robber.h"
#include "../include/npc/werewolf.h"
#include "../include/npc/princess.h"
#include "../include/npc/toad.h"
#include "../include/npc/slaver.h"
#include "../include/npc/pegasus.h"
#include "../include/npc/bittern.h"
#include "../include/npc/desman.h"
#include "../include/npc/bull.h"
#include "../include/visitor/battle_visitor.h"
#include "../include/factory/npc_factory.h"
#include "../include/game/game_constants.h"

TEST(NPCTest, CreationAndParameters) {
    // Test all NPC types creation
    auto orc = std::make_shared<Orc>(100, 200, "Grom");
    EXPECT_EQ(orc->getType(), NpcType::Orc);
    EXPECT_EQ(orc->getName(), "Grom");
    EXPECT_EQ(orc->getX(), 100);
    EXPECT_EQ(orc->getY(), 200);
    EXPECT_TRUE(orc->isAlive());
    EXPECT_EQ(orc->getMoveDistance(), 20);
    EXPECT_EQ(orc->getKillDistance(), 10);
    EXPECT_EQ(orc->getTypeName(), "Orc");
    
    auto squirrel = std::make_shared<Squirrel>(50, 150, "Chip");
    EXPECT_EQ(squirrel->getType(), NpcType::Squirrel);
    EXPECT_EQ(squirrel->getMoveDistance(), 5);
    EXPECT_EQ(squirrel->getKillDistance(), 5);
    
    auto druid = std::make_shared<Druid>(200, 300, "Malfurion");
    EXPECT_EQ(druid->getType(), NpcType::Druid);
    EXPECT_EQ(druid->getMoveDistance(), 10);
    EXPECT_EQ(druid->getKillDistance(), 10);
    
    // Test all other NPC types
    auto knight = std::make_shared<Knight>(0, 0, "Arthur");
    EXPECT_EQ(knight->getType(), NpcType::Knight);
    EXPECT_EQ(knight->getMoveDistance(), 30);
    
    auto elf = std::make_shared<Elf>(10, 20, "Legolas");
    EXPECT_EQ(elf->getType(), NpcType::Elf);
    EXPECT_EQ(elf->getKillDistance(), 50);  // Longest kill distance
    
    auto dragon = std::make_shared<Dragon>(30, 40, "Smaug");
    EXPECT_EQ(dragon->getType(), NpcType::Dragon);
    EXPECT_EQ(dragon->getMoveDistance(), 50);  // Longest move distance
    
    auto bear = std::make_shared<Bear>(5, 5, "Baloo");
    EXPECT_EQ(bear->getType(), NpcType::Bear);
    
    auto robber = std::make_shared<Robber>(15, 25, "Robin");
    EXPECT_EQ(robber->getType(), NpcType::Robber);
    
    auto werewolf = std::make_shared<Werewolf>(40, 50, "Fenrir");
    EXPECT_EQ(werewolf->getType(), NpcType::Werewolf);
    EXPECT_EQ(werewolf->getMoveDistance(), 40);
    
    auto princess = std::make_shared<Princess>(1, 1, "Aurora");
    EXPECT_EQ(princess->getType(), NpcType::Princess);
    EXPECT_EQ(princess->getMoveDistance(), 1);
    EXPECT_EQ(princess->getKillDistance(), 1);
    
    auto toad = std::make_shared<Toad>(2, 2, "Ribbit");
    EXPECT_EQ(toad->getType(), NpcType::Toad);
    
    auto slaver = std::make_shared<Slaver>(25, 35, "Keto");
    EXPECT_EQ(slaver->getType(), NpcType::Slaver);
    
    auto pegasus = std::make_shared<Pegasus>(60, 70, "Sky");
    EXPECT_EQ(pegasus->getType(), NpcType::Pegasus);
    
    auto bittern = std::make_shared<Bittern>(70, 80, "Heron");
    EXPECT_EQ(bittern->getType(), NpcType::Bittern);
    
    auto desman = std::make_shared<Desman>(80, 90, "Digger");
    EXPECT_EQ(desman->getType(), NpcType::Desman);
    EXPECT_EQ(desman->getKillDistance(), 20);
    
    auto bull = std::make_shared<Bull>(90, 100, "Ferdinand");
    EXPECT_EQ(bull->getType(), NpcType::Bull);
}

TEST(NPCTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Orc>(0, 0, "Grom");
    auto npc2 = std::make_shared<Squirrel>(3, 4, "Chip");
    
    EXPECT_DOUBLE_EQ(npc1->distanceTo(npc2), 5.0);
    
    // Test with negative coordinates
    auto npc3 = std::make_shared<Druid>(-3, -4, "Malfurion");
    EXPECT_DOUBLE_EQ(npc1->distanceTo(npc3), 5.0);
}

TEST(NPCTest, ThreadSafety) {
    auto npc = std::make_shared<Orc>(0, 0, "TestOrc");
    
    // Test concurrent access
    std::thread t1([&npc]() {
        for (int i = 0; i < 1000; ++i) {
            npc->getX();
            npc->getY();
        }
    });
    
    std::thread t2([&npc]() {
        for (int i = 0; i < 1000; ++i) {
            npc->setPosition(i % 100, i % 100);
        }
    });
    
    std::thread t3([&npc]() {
        for (int i = 0; i < 1000; ++i) {
            npc->toString();
        }
    });
    
    t1.join();
    t2.join();
    t3.join();
    
    // Should not crash
    EXPECT_TRUE(npc->isAlive());
}

TEST(NPCTest, Movement) {
    auto npc = std::make_shared<Orc>(50, 50, "MovingOrc");
    int initialX = npc->getX();
    int initialY = npc->getY();
    
    npc->moveRandomly();
    
    // Should move within bounds
    int newX = npc->getX();
    int newY = npc->getY();
    
    EXPECT_GE(newX, 0);
    EXPECT_LT(newX, GameConstants::MAP_WIDTH);
    EXPECT_GE(newY, 0);
    EXPECT_LT(newY, GameConstants::MAP_HEIGHT);
    
    // Should not move more than move distance
    EXPECT_LE(std::abs(newX - initialX), npc->getMoveDistance());
    EXPECT_LE(std::abs(newY - initialY), npc->getMoveDistance());
}

TEST(NPCTest, CanMoveTo) {
    auto npc = std::make_shared<Orc>(50, 50, "TestOrc");
    
    // Valid positions
    EXPECT_TRUE(npc->canMoveTo(0, 0));
    EXPECT_TRUE(npc->canMoveTo(GameConstants::MAP_WIDTH - 1, GameConstants::MAP_HEIGHT - 1));
    EXPECT_TRUE(npc->canMoveTo(50, 50));  // Same position
    
    // Invalid positions
    EXPECT_FALSE(npc->canMoveTo(-1, 50));
    EXPECT_FALSE(npc->canMoveTo(50, -1));
    EXPECT_FALSE(npc->canMoveTo(GameConstants::MAP_WIDTH, 50));
    EXPECT_FALSE(npc->canMoveTo(50, GameConstants::MAP_HEIGHT));
}

TEST(NPCTest, DiceRolls) {
    auto npc = std::make_shared<Orc>(0, 0, "DiceOrc");
    
    // Roll dice multiple times to ensure it's within bounds
    for (int i = 0; i < 100; ++i) {
        int attack = npc->rollAttackDice();
        int defense = npc->rollDefenseDice();
        
        EXPECT_GE(attack, 1);
        EXPECT_LE(attack, 6);
        EXPECT_GE(defense, 1);
        EXPECT_LE(defense, 6);
    }
}

TEST(BattleVisitorTest, OrcVisitor) {
    auto orcVisitor = std::make_shared<OrcVisitor>();
    
    // Create different NPCs
    auto orc = std::make_shared<Orc>(0, 0, "Orc");
    auto druid = std::make_shared<Druid>(1, 0, "Druid");
    auto squirrel = std::make_shared<Squirrel>(2, 0, "Squirrel");
    auto elf = std::make_shared<Elf>(3, 0, "Elf");
    
    // Orc kills Druid
    EXPECT_TRUE(druid->accept(orcVisitor));
    
    // Orc kills Elf
    EXPECT_TRUE(elf->accept(orcVisitor));
    
    // Orc doesn't kill Squirrel
    EXPECT_FALSE(squirrel->accept(orcVisitor));
    
    // Orc doesn't kill Orc (same type)
    EXPECT_FALSE(orc->accept(orcVisitor));
}

TEST(BattleVisitorTest, SquirrelVisitor) {
    auto squirrelVisitor = std::make_shared<SquirrelVisitor>();
    
    auto squirrel = std::make_shared<Squirrel>(0, 0, "Squirrel");
    auto orc = std::make_shared<Orc>(1, 0, "Orc");
    auto druid = std::make_shared<Druid>(2, 0, "Druid");
    
    // Squirrel is peaceful - never kills anyone
    EXPECT_FALSE(orc->accept(squirrelVisitor));
    EXPECT_FALSE(druid->accept(squirrelVisitor));
    EXPECT_FALSE(squirrel->accept(squirrelVisitor));
}

TEST(BattleVisitorTest, DruidVisitor) {
    auto druidVisitor = std::make_shared<DruidVisitor>();
    
    auto druid = std::make_shared<Druid>(0, 0, "Druid");
    auto squirrel = std::make_shared<Squirrel>(1, 0, "Squirrel");
    auto orc = std::make_shared<Orc>(2, 0, "Orc");
    auto dragon = std::make_shared<Dragon>(3, 0, "Dragon");
    
    // Druid kills Squirrel
    EXPECT_TRUE(squirrel->accept(druidVisitor));
    
    // Druid kills Dragon
    EXPECT_TRUE(dragon->accept(druidVisitor));
    
    // Druid doesn't kill Orc
    EXPECT_FALSE(orc->accept(druidVisitor));
    
    // Druid doesn't kill Druid (same type)
    EXPECT_FALSE(druid->accept(druidVisitor));
}

TEST(FactoryTest, CreateNPC) {
    // Test creating all NPC types
    auto orc = NPCFactory::createNPC(NpcType::Orc, 10, 20, "Grom");
    EXPECT_EQ(orc->getType(), NpcType::Orc);
    EXPECT_EQ(orc->getX(), 10);
    EXPECT_EQ(orc->getY(), 20);
    EXPECT_EQ(orc->getName(), "Grom");
    
    auto squirrel = NPCFactory::createNPC(NpcType::Squirrel, 30, 40, "Chip");
    EXPECT_EQ(squirrel->getType(), NpcType::Squirrel);
    
    auto druid = NPCFactory::createNPC(NpcType::Druid, 50, 60, "Malfurion");
    EXPECT_EQ(druid->getType(), NpcType::Druid);
    
    // Test creating all other types
    auto knight = NPCFactory::createNPC(NpcType::Knight, 0, 0, "Arthur");
    EXPECT_EQ(knight->getType(), NpcType::Knight);
    
    auto elf = NPCFactory::createNPC(NpcType::Elf, 1, 1, "Legolas");
    EXPECT_EQ(elf->getType(), NpcType::Elf);
    
    auto dragon = NPCFactory::createNPC(NpcType::Dragon, 2, 2, "Smaug");
    EXPECT_EQ(dragon->getType(), NpcType::Dragon);
    
    auto bear = NPCFactory::createNPC(NpcType::Bear, 3, 3, "Baloo");
    EXPECT_EQ(bear->getType(), NpcType::Bear);
    
    auto robber = NPCFactory::createNPC(NpcType::Robber, 4, 4, "Robin");
    EXPECT_EQ(robber->getType(), NpcType::Robber);
    
    auto werewolf = NPCFactory::createNPC(NpcType::Werewolf, 5, 5, "Fenrir");
    EXPECT_EQ(werewolf->getType(), NpcType::Werewolf);
    
    auto princess = NPCFactory::createNPC(NpcType::Princess, 6, 6, "Aurora");
    EXPECT_EQ(princess->getType(), NpcType::Princess);
    
    auto toad = NPCFactory::createNPC(NpcType::Toad, 7, 7, "Ribbit");
    EXPECT_EQ(toad->getType(), NpcType::Toad);
    
    auto slaver = NPCFactory::createNPC(NpcType::Slaver, 8, 8, "Keto");
    EXPECT_EQ(slaver->getType(), NpcType::Slaver);
    
    auto pegasus = NPCFactory::createNPC(NpcType::Pegasus, 9, 9, "Sky");
    EXPECT_EQ(pegasus->getType(), NpcType::Pegasus);
    
    auto bittern = NPCFactory::createNPC(NpcType::Bittern, 10, 10, "Heron");
    EXPECT_EQ(bittern->getType(), NpcType::Bittern);
    
    auto desman = NPCFactory::createNPC(NpcType::Desman, 11, 11, "Digger");
    EXPECT_EQ(desman->getType(), NpcType::Desman);
    
    auto bull = NPCFactory::createNPC(NpcType::Bull, 12, 12, "Ferdinand");
    EXPECT_EQ(bull->getType(), NpcType::Bull);
}

TEST(FactoryTest, RandomNPC) {
    // Create multiple random NPCs
    std::vector<std::shared_ptr<NPC>> npcs;
    
    for (int i = 0; i < 100; ++i) {
        auto npc = NPCFactory::createRandomNPC();
        npcs.push_back(npc);
        
        // Should be within map bounds
        EXPECT_GE(npc->getX(), 0);
        EXPECT_LT(npc->getX(), GameConstants::MAP_WIDTH);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LT(npc->getY(), GameConstants::MAP_HEIGHT);
        
        // Should have a name
        EXPECT_FALSE(npc->getName().empty());
    }
    
    // Should have various types
    std::set<NpcType> types;
    for (const auto& npc : npcs) {
        types.insert(npc->getType());
    }
    
    // Should have at least several different types
    EXPECT_GT(types.size(), 5);
}

TEST(FactoryTest, SerializeDeserialize) {
    // Test serialization/deserialization for all types
    std::vector<std::shared_ptr<NPC>> originalNPCs = {
        std::make_shared<Orc>(100, 200, "Grom Hellscream"),
        std::make_shared<Squirrel>(50, 150, "Chip the Brave"),
        std::make_shared<Druid>(200, 300, "Malfurion Stormrage"),
        std::make_shared<Knight>(0, 0, "Arthur Pendragon"),
        std::make_shared<Elf>(10, 20, "Legolas Greenleaf"),
        std::make_shared<Dragon>(30, 40, "Smaug the Golden"),
        std::make_shared<Bear>(5, 5, "Baloo the Bear"),
        std::make_shared<Robber>(15, 25, "Robin Hood"),
        std::make_shared<Werewolf>(40, 50, "Fenrir Wolfborn"),
        std::make_shared<Princess>(1, 1, "Princess Aurora"),
        std::make_shared<Toad>(2, 2, "Mr. Ribbit"),
        std::make_shared<Slaver>(25, 35, "Keto the Slaver"),
        std::make_shared<Pegasus>(60, 70, "Sky Cloud"),
        std::make_shared<Bittern>(70, 80, "Heron Egret"),
        std::make_shared<Desman>(80, 90, "Digger Mole"),
        std::make_shared<Bull>(90, 100, "Ferdinand the Bull")
    };
    
    for (const auto& original : originalNPCs) {
        // Serialize
        std::string data = NPCFactory::serializeNPC(original);
        
        // Deserialize
        auto loaded = NPCFactory::createNPCFromString(data);
        
        // Should match
        EXPECT_EQ(loaded->getType(), original->getType());
        EXPECT_EQ(loaded->getX(), original->getX());
        EXPECT_EQ(loaded->getY(), original->getY());
        EXPECT_EQ(loaded->getName(), original->getName());
        
        // Test toString
        EXPECT_EQ(loaded->toString(), original->toString());
    }
    
    // Test with spaces in name
    auto npcWithSpace = std::make_shared<Orc>(123, 456, "Grom Hellscream the Destroyer");
    std::string data = NPCFactory::serializeNPC(npcWithSpace);
    auto loaded = NPCFactory::createNPCFromString(data);
    
    EXPECT_EQ(loaded->getName(), "Grom Hellscream the Destroyer");
}

TEST(FactoryTest, GetMoveKillDistances) {
    // Test all NPC distances from table
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Orc), 20);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Orc), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Squirrel), 5);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Squirrel), 5);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Druid), 10);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Druid), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Knight), 30);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Knight), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Elf), 10);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Elf), 50);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Dragon), 50);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Dragon), 30);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Bear), 5);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Bear), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Robber), 10);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Robber), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Werewolf), 40);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Werewolf), 5);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Princess), 1);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Princess), 1);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Toad), 1);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Toad), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Slaver), 10);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Slaver), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Pegasus), 30);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Pegasus), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Bittern), 50);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Bittern), 10);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Desman), 5);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Desman), 20);
    
    EXPECT_EQ(NPCFactory::getMoveDistance(NpcType::Bull), 30);
    EXPECT_EQ(NPCFactory::getKillDistance(NpcType::Bull), 10);
}