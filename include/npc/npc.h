#pragma once


#include <string>
#include <memory>
#include <random>
#include <mutex>
#include <shared_mutex>
#include "../game/game_constants.h"

enum class NpcType {
    Orc,
    Squirrel,
    Druid,
    Knight,
    Elf,
    Dragon,
    Bear,
    Robber,
    Werewolf,
    Princess,
    Toad,
    Slaver,
    Pegasus,
    Bittern,
    Desman,
    Bull
};

class BattleVisitor;

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    int x;
    int y;
    std::string name;
    NpcType type;
    bool alive;
    
    // Параметры движения и атаки
    int moveDistance;
    int killDistance;
    
    // Мьютексы для потокобезопасности
    mutable std::shared_mutex positionMutex;
    mutable std::shared_mutex stateMutex;
    
    // Генератор случайных чисел для кубика
    static std::mt19937 randomGen;
    static std::uniform_int_distribution<int> diceDist;
    
public:
    NPC(int x, int y, const std::string& name, NpcType type, 
         int moveDist, int killDist);
    virtual ~NPC() = default;
    
    virtual bool accept(const std::shared_ptr<BattleVisitor>& attacker) = 0;
    
    // Потокобезопасные методы
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    std::string getName() const;
    NpcType getType() const; 
    bool isAlive() const; 
    void kill();
    
    int getMoveDistance() const;
    int getKillDistance() const;
    
    virtual std::string getTypeName() const = 0;
    double distanceTo(const std::shared_ptr<NPC>& other) const;
    
    // Методы для движения
    void moveRandomly();
    bool canMoveTo(int newX, int newY) const;
    
    // Методы для боя с кубиком
    int rollAttackDice() const;
    int rollDefenseDice() const;
    bool fight(const std::shared_ptr<NPC>& defender) const;
    
    virtual std::string toString() const;
    
    // Статические методы
    static void initRandom();
};