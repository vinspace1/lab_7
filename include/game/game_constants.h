#pragma once


#include <cstddef>

namespace GameConstants {
    // Размеры карты
    constexpr int MAP_WIDTH = 100;
    constexpr int MAP_HEIGHT = 100;
    
    // Время игры (секунды)
    constexpr int GAME_DURATION = 30;
    
    // Количество NPC при старте
    constexpr size_t INITIAL_NPC_COUNT = 50;
    
    // Диапазон броска кубика
    constexpr int DICE_MIN = 1;
    constexpr int DICE_MAX = 6;
    
    // Время между обновлениями (мс)
    constexpr int MOVE_UPDATE_MS = 100;
    constexpr int BATTLE_UPDATE_MS = 50;
    constexpr int PRINT_UPDATE_MS = 1000;
}