#include "../include/dungeon_editor.h"
#include "../include/observer/console_observer.h"
#include "../include/observer/file_observer.h"
#include <iostream>
#include <thread>

int main() {
    try {
        std::cout << "========================================" << std::endl;
        std::cout << "   Dungeon Game for Balagur Fate 3     " << std::endl;
        std::cout << "        Multi-threaded Edition         " << std::endl;
        std::cout << "========================================" << std::endl;
        
        DungeonEditor editor;
        
        // Add observers
        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>("game_log.txt");
        
        editor.addObserver(consoleObserver);
        editor.addObserver(fileObserver);
        
        std::cout << "\nStarting game..." << std::endl;
        std::cout << "Game will run for 30 seconds." << std::endl;
        std::cout << "50 NPCs will be randomly generated." << std::endl;
        std::cout << "Press Ctrl+C to exit early.\n" << std::endl;
        
        // Start the game
        editor.startGame();
        
        // Wait for game to finish
        while (!editor.isGameOver()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cout << "\nGame finished!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}