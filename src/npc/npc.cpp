#include "../../include/npc/npc.h"
#include <cmath>
#include <string>
#include <chrono>
#include <random>

// Инициализация статических членов
std::mt19937 NPC::randomGen(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> NPC::diceDist(1, 6);

NPC::NPC(int x, int y, const std::string& name, NpcType type, 
         int moveDist, int killDist)
    : x(x), y(y), name(name), type(type), alive(true),
      moveDistance(moveDist), killDistance(killDist) {
}

int NPC::getX() const {
    std::shared_lock lock(positionMutex);
    return x;
}

int NPC::getY() const {
    std::shared_lock lock(positionMutex);
    return y;
}

void NPC::setPosition(int newX, int newY) {
    std::unique_lock lock(positionMutex);
    x = newX;
    y = newY;
}

std::string NPC::getName() const {
    std::shared_lock lock(stateMutex);
    return name;
}

NpcType NPC::getType() const {
    std::shared_lock lock(stateMutex);
    return type;
}

bool NPC::isAlive() const {
    std::shared_lock lock(stateMutex);
    return alive;
}

void NPC::kill() {
    std::unique_lock lock(stateMutex);
    alive = false;
}

int NPC::getMoveDistance() const {
    std::shared_lock lock(stateMutex);
    return moveDistance;
}

int NPC::getKillDistance() const {
    std::shared_lock lock(stateMutex);
    return killDistance;
}

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    int otherX = other->getX();
    int otherY = other->getY();
    
    std::shared_lock lock(positionMutex);
    int dx = x - otherX;
    int dy = y - otherY;
    return std::sqrt(dx*dx + dy*dy);
}

void NPC::moveRandomly() {
    if (!isAlive()) return;
    
    std::uniform_int_distribution<int> moveDist(-moveDistance, moveDistance);
    
    int newX, newY;
    do {
        std::shared_lock lock(positionMutex);
        newX = x + moveDist(randomGen);
        newY = y + moveDist(randomGen);
    } while (!canMoveTo(newX, newY));
    
    setPosition(newX, newY);
}

bool NPC::canMoveTo(int newX, int newY) const {
    return newX >= 0 && newX < GameConstants::MAP_WIDTH &&
           newY >= 0 && newY < GameConstants::MAP_HEIGHT;
}

int NPC::rollAttackDice() const {
    return diceDist(randomGen);
}

int NPC::rollDefenseDice() const {
    return diceDist(randomGen);
}

bool NPC::fight(const std::shared_ptr<NPC>& defender) const {
    int attack = rollAttackDice();
    int defense = defender->rollDefenseDice();
    return attack > defense;
}

std::string NPC::toString() const {
    std::shared_lock lock1(stateMutex);
    std::shared_lock lock2(positionMutex);
    
    return getTypeName() + " '" + name + "' at (" + 
           std::to_string(x) + ", " + std::to_string(y) + ")";
}

void NPC::initRandom() {}