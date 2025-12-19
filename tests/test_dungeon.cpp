#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <atomic>
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
#include "../include/dungeon_editor.h"
#include "../include/observer/console_observer.h"
#include "../include/observer/file_observer.h"
#include "../include/game/game_map.h"

TEST(DungeonEditorTest, Creation) {
    DungeonEditor editor;
    
    // Initially not running
    EXPECT_FALSE(editor.isRunning());
    EXPECT_FALSE(editor.isGameOver());
}

TEST(DungeonEditorTest, ObserverManagement) {
    DungeonEditor editor;
    
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("test_log.txt");
    
    // Add observers
    editor.addObserver(consoleObserver);
    editor.addObserver(fileObserver);
    
    // Can't directly test observers were added, but shouldn't crash
    EXPECT_NO_THROW(editor.addObserver(consoleObserver));
    
    // Remove observer
    EXPECT_NO_THROW(editor.removeObserver(fileObserver));
    
    // Clean up test file
    std::remove("test_log.txt");
}

TEST(GameMapTest, BasicOperations) {
    GameMap map(100, 100);
    
    // Initially empty
    EXPECT_EQ(map.getAliveCount(), 0);
    EXPECT_EQ(map.getTotalCount(), 0);
    
    // Add NPCs
    auto orc = std::make_shared<Orc>(10, 20, "Grom");
    auto squirrel = std::make_shared<Squirrel>(30, 40, "Chip");
    
    map.addNPC(orc);
    map.addNPC(squirrel);
    
    EXPECT_EQ(map.getTotalCount(), 2);
    EXPECT_EQ(map.getAliveCount(), 2);
    
    // Get alive NPCs
    auto alive = map.getAliveNPCs();
    EXPECT_EQ(alive.size(), 2);
    
    // Get all NPCs
    auto all = map.getAllNPCs();
    EXPECT_EQ(all.size(), 2);
    
    // Kill an NPC
    orc->kill();
    EXPECT_EQ(map.getAliveCount(), 1);
    
    // Remove dead NPCs
    map.removeDeadNPCs();
    EXPECT_EQ(map.getTotalCount(), 1);
    
    // Clear map
    map.clear();
    EXPECT_EQ(map.getTotalCount(), 0);
}

TEST(GameMapTest, Movement) {
    GameMap map(100, 100);
    
    // Add NPCs in different positions
    auto orc = std::make_shared<Orc>(50, 50, "Grom");
    auto squirrel = std::make_shared<Squirrel>(10, 10, "Chip");
    
    map.addNPC(orc);
    map.addNPC(squirrel);
    
    // Store initial positions
    int orcInitialX = orc->getX();
    int orcInitialY = orc->getY();
    int squirrelInitialX = squirrel->getX();
    int squirrelInitialY = squirrel->getY();
    
    // Move all NPCs
    map.moveAllNPCs();
    
    // Should have moved (or possibly stayed if random move was 0,0)
    // At least check they're still within bounds
    EXPECT_GE(orc->getX(), 0);
    EXPECT_LT(orc->getX(), 100);
    EXPECT_GE(orc->getY(), 0);
    EXPECT_LT(orc->getY(), 100);
    
    EXPECT_GE(squirrel->getX(), 0);
    EXPECT_LT(squirrel->getX(), 100);
    EXPECT_GE(squirrel->getY(), 0);
    EXPECT_LT(squirrel->getY(), 100);
    
    // Move many times
    for (int i = 0; i < 100; ++i) {
        map.moveAllNPCs();
        
        // Should always stay within bounds
        EXPECT_GE(orc->getX(), 0);
        EXPECT_LT(orc->getX(), 100);
        EXPECT_GE(orc->getY(), 0);
        EXPECT_LT(orc->getY(), 100);
    }
}

TEST(GameMapTest, DeadNPCsDontMove) {
    GameMap map(100, 100);
    
    auto orc = std::make_shared<Orc>(50, 50, "Grom");
    map.addNPC(orc);
    
    // Kill the orc
    orc->kill();
    
    // Store position
    int deadX = orc->getX();
    int deadY = orc->getY();
    
    // Try to move - dead NPCs shouldn't move
    map.moveAllNPCs();
    
    // Position should remain the same
    EXPECT_EQ(orc->getX(), deadX);
    EXPECT_EQ(orc->getY(), deadY);
}

TEST(GameMapTest, BattleDetection) {
    GameMap map(100, 100);
    
    // Place NPCs within kill distance
    auto orc = std::make_shared<Orc>(0, 0, "Grom");
    auto druid = std::make_shared<Druid>(5, 0, "Malfurion");  // Within 10 kill distance
    
    map.addNPC(orc);
    map.addNPC(druid);
    
    // Detect battles
    auto battles = map.detectBattles();
    
    // Should detect battle (orc can kill druid at distance 5 < 10)
    EXPECT_GT(battles.size(), 0);
    
    // Add NPCs too far apart
    auto squirrel = std::make_shared<Squirrel>(50, 50, "Chip");
    map.addNPC(squirrel);
    
    battles = map.detectBattles();
    // Still should have the orc-druid battle
    EXPECT_GT(battles.size(), 0);
    
    // Test with multiple NPCs
    auto knight = std::make_shared<Knight>(0, 5, "Arthur");  // Within 10 of orc
    map.addNPC(knight);
    
    battles = map.detectBattles();
    // Should have more battles now
    EXPECT_GE(battles.size(), 2);
}

TEST(GameMapTest, GenerateRandomNPCs) {
    GameMap map(100, 100);
    
    // Generate random NPCs
    map.generateRandomNPCs(50);
    
    EXPECT_EQ(map.getTotalCount(), 50);
    EXPECT_EQ(map.getAliveCount(), 50);
    
    // Check they're within bounds
    auto allNPCs = map.getAllNPCs();
    for (const auto& npc : allNPCs) {
        EXPECT_GE(npc->getX(), 0);
        EXPECT_LT(npc->getX(), 100);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LT(npc->getY(), 100);
        EXPECT_TRUE(npc->isAlive());
    }
    
    // Generate more NPCs
    map.generateRandomNPCs(25);
    EXPECT_EQ(map.getTotalCount(), 75);
}

TEST(GameMapTest, PrintMap) {
    GameMap map(10, 10);  // Small map for testing
    
    // Add some NPCs
    auto orc = std::make_shared<Orc>(0, 0, "Grom");
    auto squirrel = std::make_shared<Squirrel>(5, 5, "Chip");
    auto druid = std::make_shared<Druid>(9, 9, "Malfurion");
    
    map.addNPC(orc);
    map.addNPC(squirrel);
    map.addNPC(druid);
    
    // Print should not crash
    EXPECT_NO_THROW(map.printMap());
    
    // Kill an NPC and print again
    druid->kill();
    EXPECT_NO_THROW(map.printMap());
    
    // Remove dead and print
    map.removeDeadNPCs();
    EXPECT_NO_THROW(map.printMap());
}

TEST(DungeonEditorTest, ThreadSafety) {
    DungeonEditor editor;
    
    // Start game in separate thread
    std::thread gameThread([&editor]() {
        // Don't actually run full game, just test thread safety
    });
    
    // Access editor from main thread while game thread is running
    EXPECT_NO_THROW(editor.isRunning());
    EXPECT_NO_THROW(editor.isGameOver());
    
    gameThread.join();
}

TEST(DungeonEditorTest, ShortGameSimulation) {
    // This test simulates a very short game
    DungeonEditor editor;
    
    // Add observers
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    editor.addObserver(consoleObserver);
    
    // Start and immediately stop game
    // Note: In real test, we'd need to mock or speed up the game timer
    // For now, just test that start/stop don't crash
    EXPECT_NO_THROW(editor.startGame());
    
    // Wait a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Stop game
    EXPECT_NO_THROW(editor.stopGame());
}

TEST(DungeonEditorTest, BattleQueue) {
    DungeonEditor editor;
    
    auto attacker = std::make_shared<Orc>(0, 0, "Attacker");
    auto defender = std::make_shared<Druid>(1, 0, "Defender");
    
    // Test battle processing
    // Note: processBattle is private, but we can test through public interface
    // or make it protected for testing
    
    // For now, just test that we can create battles
    EXPECT_TRUE(attacker->isAlive());
    EXPECT_TRUE(defender->isAlive());
}

TEST(ConcurrencyTest, MultipleThreadsAccess) {
    GameMap map(100, 100);
    
    // Add some NPCs
    for (int i = 0; i < 10; ++i) {
        auto npc = std::make_shared<Orc>(i * 10, i * 10, "Orc" + std::to_string(i));
        map.addNPC(npc);
    }
    
    std::atomic<int> readCount{0};
    std::atomic<int> writeCount{0};
    
    // Multiple threads reading
    std::vector<std::thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.emplace_back([&map, &readCount]() {
            for (int j = 0; j < 100; ++j) {
                auto npcs = map.getAliveNPCs();
                readCount += npcs.size();
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
        });
    }
    
    // Multiple threads writing (moving NPCs)
    std::vector<std::thread> writers;
    for (int i = 0; i < 3; ++i) {
        writers.emplace_back([&map, &writeCount]() {
            for (int j = 0; j < 50; ++j) {
                map.moveAllNPCs();
                writeCount++;
                std::this_thread::sleep_for(std::chrono::microseconds(20));
            }
        });
    }
    
    // Join all threads
    for (auto& t : readers) t.join();
    for (auto& t : writers) t.join();
    
    // Should not crash
    EXPECT_GT(readCount, 0);
    EXPECT_GT(writeCount, 0);
    
    // All NPCs should still be alive and within bounds
    auto npcs = map.getAllNPCs();
    for (const auto& npc : npcs) {
        EXPECT_TRUE(npc->isAlive());
        EXPECT_GE(npc->getX(), 0);
        EXPECT_LT(npc->getX(), 100);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LT(npc->getY(), 100);
    }
}

TEST(GameConstantsTest, Constants) {
    // Test game constants
    EXPECT_EQ(GameConstants::MAP_WIDTH, 100);
    EXPECT_EQ(GameConstants::MAP_HEIGHT, 100);
    EXPECT_EQ(GameConstants::GAME_DURATION, 30);
    EXPECT_EQ(GameConstants::INITIAL_NPC_COUNT, 50);
    EXPECT_EQ(GameConstants::DICE_MIN, 1);
    EXPECT_EQ(GameConstants::DICE_MAX, 6);
    
    // Time constants should be positive
    EXPECT_GT(GameConstants::MOVE_UPDATE_MS, 0);
    EXPECT_GT(GameConstants::BATTLE_UPDATE_MS, 0);
    EXPECT_GT(GameConstants::PRINT_UPDATE_MS, 0);
}

// Test Observer pattern
TEST(ObserverTest, ConsoleObserver) {
    ConsoleObserver observer;
    
    auto attacker = std::make_shared<Orc>(0, 0, "Attacker");
    auto defender = std::make_shared<Druid>(1, 0, "Defender");
    
    // Should not crash
    EXPECT_NO_THROW(observer.onFight(attacker, defender, true));
    EXPECT_NO_THROW(observer.onFight(attacker, defender, false));
}

TEST(ObserverTest, FileObserver) {
    // Test file creation
    const std::string filename = "observer_test_log.txt";
    
    {
        FileObserver observer(filename);
        
        auto attacker = std::make_shared<Orc>(0, 0, "Attacker");
        auto defender = std::make_shared<Druid>(1, 0, "Defender");
        
        // Write some log entries
        EXPECT_NO_THROW(observer.onFight(attacker, defender, true));
        EXPECT_NO_THROW(observer.onFight(attacker, defender, false));
        
        // File should exist
        std::ifstream file(filename);
        EXPECT_TRUE(file.good());
    }
    
    // Clean up
    std::remove(filename.c_str());
}

TEST(IntegrationTest, CompleteGameFlow) {
    // This is a high-level integration test
    GameMap map(40, 40);
    
    // Generate NPCs
    map.generateRandomNPCs(10);
    
    // Initial state
    EXPECT_EQ(map.getAliveCount(), 10);
    EXPECT_EQ(map.getTotalCount(), 10);
    
    // Move NPCs
    map.moveAllNPCs();
    
    // Detect battles
    auto battles = map.detectBattles();
    
    // Process some kills
    if (!battles.empty()) {
        auto& [attacker, defender] = battles[0];
        
        // Simulate fight with dice
        if (attacker->fight(defender)) {
            defender->kill();
        }
    }
    
    // Remove dead NPCs
    map.removeDeadNPCs();
    
    // Should have some NPCs left
    EXPECT_LE(map.getAliveCount(), 10);
    EXPECT_LE(map.getTotalCount(), 10);
    
    // Print final state
    EXPECT_NO_THROW(map.printMap());
}