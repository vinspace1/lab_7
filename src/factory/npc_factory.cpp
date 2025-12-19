#include "../../include/factory/npc_factory.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/squirrel.h"
#include "../../include/npc/druid.h"
#include "../../include/npc/knight.h"
#include "../../include/npc/elf.h"
#include "../../include/npc/dragon.h"
#include "../../include/npc/bear.h"
#include "../../include/npc/robber.h"
#include "../../include/npc/werewolf.h"
#include "../../include/npc/princess.h"
#include "../../include/npc/toad.h"
#include "../../include/npc/slaver.h"
#include "../../include/npc/pegasus.h"
#include "../../include/npc/bittern.h"
#include "../../include/npc/desman.h"
#include "../../include/npc/bull.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <stdexcept>

// Инициализация статических членов
std::mt19937 NPCFactory::randomGen(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> NPCFactory::posDist(0, 99);
std::uniform_int_distribution<int> NPCFactory::typeDist(0, 15);

void NPCFactory::initRandom() {
    // Уже инициализировано
}

std::shared_ptr<NPC> NPCFactory::createNPC(
    NpcType type, 
    int x, 
    int y, 
    const std::string& name
) {
    int moveDist = getMoveDistance(type);
    int killDist = getKillDistance(type);
    
    switch (type) {
        case NpcType::Orc:
            return std::make_shared<Orc>(x, y, name);
        case NpcType::Squirrel:
            return std::make_shared<Squirrel>(x, y, name);
        case NpcType::Druid:
            return std::make_shared<Druid>(x, y, name);
        case NpcType::Knight:
            return std::make_shared<Knight>(x, y, name);
        case NpcType::Elf:
            return std::make_shared<Elf>(x, y, name);
        case NpcType::Dragon:
            return std::make_shared<Dragon>(x, y, name);
        case NpcType::Bear:
            return std::make_shared<Bear>(x, y, name);
        case NpcType::Robber:
            return std::make_shared<Robber>(x, y, name);
        case NpcType::Werewolf:
            return std::make_shared<Werewolf>(x, y, name);
        case NpcType::Princess:
            return std::make_shared<Princess>(x, y, name);
        case NpcType::Toad:
            return std::make_shared<Toad>(x, y, name);
        case NpcType::Slaver:
            return std::make_shared<Slaver>(x, y, name);
        case NpcType::Pegasus:
            return std::make_shared<Pegasus>(x, y, name);
        case NpcType::Bittern:
            return std::make_shared<Bittern>(x, y, name);
        case NpcType::Desman:
            return std::make_shared<Desman>(x, y, name);
        case NpcType::Bull:
            return std::make_shared<Bull>(x, y, name);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<NPC> NPCFactory::createRandomNPC() {
    NpcType type = static_cast<NpcType>(typeDist(randomGen));
    int x = posDist(randomGen);
    int y = posDist(randomGen);
    std::string name = getRandomName(type);
    
    return createNPC(type, x, y, name);
}

std::string NPCFactory::getRandomName(NpcType type) {
    static std::vector<std::string> orcNames = {"Grom", "Thrall", "Guldan", "Garrosh", "Durotan"};
    static std::vector<std::string> squirrelNames = {"Chip", "Dale", "Rocky", "Alvin", "Sandy"};
    static std::vector<std::string> druidNames = {"Malfurion", "Cenarius", "Elune", "Fandral", "Hamuul"};
    static std::vector<std::string> knightNames = {"Arthur", "Lancelot", "Gawain", "Galahad", "Bedivere"};
    static std::vector<std::string> elfNames = {"Legolas", "Galadriel", "Elrond", "Thranduil", "Arwen"};
    static std::vector<std::string> dragonNames = {"Smaug", "Drogon", "Viserion", "Alduin", "Shenron"};
    static std::vector<std::string> bearNames = {"Baloo", "Winnie", "Yogi", "Paddington", "Smokey"};
    static std::vector<std::string> robberNames = {"Robin", "John", "Will", "Much", "Alan"};
    static std::vector<std::string> werewolfNames = {"Fenrir", "Lycaon", "Remus", "Jacob", "Scott"};
    static std::vector<std::string> princessNames = {"Aurora", "Cinderella", "Belle", "Jasmine", "Ariel"};
    static std::vector<std::string> toadNames = {"Toad", "Bufo", "Ribbit", "Croak", "Hop"};
    static std::vector<std::string> slaverNames = {"Keto", "Slaad", "Morg", "Grak", "Vorn"};
    static std::vector<std::string> pegasusNames = {"Pegasus", "Sky", "Cloud", "Storm", "Wind"};
    static std::vector<std::string> bitternNames = {"Heron", "Egret", "Crane", "Stork", "Ibis"};
    static std::vector<std::string> desmanNames = {"Desman", "Mole", "Digger", "Burrow", "Tunnel"};
    static std::vector<std::string> bullNames = {"Ferdinand", "Taurus", "Horn", "Charge", "Stampede"};
    
    std::uniform_int_distribution<int> nameDist(0, 4);
    
    switch (type) {
        case NpcType::Orc:
            return orcNames[nameDist(randomGen)];
        case NpcType::Squirrel:
            return squirrelNames[nameDist(randomGen)];
        case NpcType::Druid:
            return druidNames[nameDist(randomGen)];
        case NpcType::Knight:
            return knightNames[nameDist(randomGen)];
        case NpcType::Elf:
            return elfNames[nameDist(randomGen)];
        case NpcType::Dragon:
            return dragonNames[nameDist(randomGen)];
        case NpcType::Bear:
            return bearNames[nameDist(randomGen)];
        case NpcType::Robber:
            return robberNames[nameDist(randomGen)];
        case NpcType::Werewolf:
            return werewolfNames[nameDist(randomGen)];
        case NpcType::Princess:
            return princessNames[nameDist(randomGen)];
        case NpcType::Toad:
            return toadNames[nameDist(randomGen)];
        case NpcType::Slaver:
            return slaverNames[nameDist(randomGen)];
        case NpcType::Pegasus:
            return pegasusNames[nameDist(randomGen)];
        case NpcType::Bittern:
            return bitternNames[nameDist(randomGen)];
        case NpcType::Desman:
            return desmanNames[nameDist(randomGen)];
        case NpcType::Bull:
            return bullNames[nameDist(randomGen)];
        default:
            return "Unknown";
    }
}

// Вспомогательная функция для обрезки пробелов
static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::shared_ptr<NPC> NPCFactory::createNPCFromString(const std::string& data) {
    std::string trimmed = trim(data);
    if (trimmed.empty()) {
        throw std::invalid_argument("Empty NPC data");
    }
    
    size_t firstSpace = trimmed.find(' ');
    if (firstSpace == std::string::npos) {
        throw std::invalid_argument("Invalid NPC data: missing coordinates");
    }
    
    std::string typeStr = trimmed.substr(0, firstSpace);
    
    size_t secondSpace = trimmed.find(' ', firstSpace + 1);
    if (secondSpace == std::string::npos) {
        throw std::invalid_argument("Invalid NPC data: missing Y coordinate");
    }
    
    std::string xStr = trimmed.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    
    size_t thirdSpace = trimmed.find(' ', secondSpace + 1);
    
    std::string yStr, name;
    
    if (thirdSpace == std::string::npos) {
        yStr = trimmed.substr(secondSpace + 1);
        name = "";
    } else {
        yStr = trimmed.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
        name = trim(trimmed.substr(thirdSpace + 1));
    }
    
    if (xStr.empty() || yStr.empty()) {
        throw std::invalid_argument("Invalid NPC data: empty coordinates");
    }
    
    auto isNumber = [](const std::string& s) {
        if (s.empty()) return false;
        
        size_t start = 0;
        if (s[0] == '-') {
            if (s.length() == 1) return false;
            start = 1;
        }
        
        return std::all_of(s.begin() + start, s.end(), 
               [](unsigned char c) { return std::isdigit(c); });
    };
    
    if (!isNumber(xStr) || !isNumber(yStr)) {
        throw std::invalid_argument("Invalid NPC data: coordinates must be numbers");
    }
    
    int x, y;
    try {
        x = std::stoi(xStr);
        y = std::stoi(yStr);
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid NPC data: " + std::string(e.what()));
    }
    
    NpcType type;
    if (typeStr == "Orc") {
        type = NpcType::Orc;
    } else if (typeStr == "Squirrel") {
        type = NpcType::Squirrel;
    } else if (typeStr == "Druid") {
        type = NpcType::Druid;
    } else if (typeStr == "Knight") {
        type = NpcType::Knight;
    } else if (typeStr == "Elf") {
        type = NpcType::Elf;
    } else if (typeStr == "Dragon") {
        type = NpcType::Dragon;
    } else if (typeStr == "Bear") {
        type = NpcType::Bear;
    } else if (typeStr == "Robber") {
        type = NpcType::Robber;
    } else if (typeStr == "Werewolf") {
        type = NpcType::Werewolf;
    } else if (typeStr == "Princess") {
        type = NpcType::Princess;
    } else if (typeStr == "Toad") {
        type = NpcType::Toad;
    } else if (typeStr == "Slaver") {
        type = NpcType::Slaver;
    } else if (typeStr == "Pegasus") {
        type = NpcType::Pegasus;
    } else if (typeStr == "Bittern") {
        type = NpcType::Bittern;
    } else if (typeStr == "Desman") {
        type = NpcType::Desman;
    } else if (typeStr == "Bull") {
        type = NpcType::Bull;
    } else {
        throw std::invalid_argument("Unknown NPC type: " + typeStr);
    }
    
    return createNPC(type, x, y, name);
}

std::string NPCFactory::serializeNPC(const std::shared_ptr<NPC>& npc) {
    return npc->getTypeName() + " " +
           std::to_string(npc->getX()) + " " +
           std::to_string(npc->getY()) + " " +
           npc->getName();
}

int NPCFactory::getMoveDistance(NpcType type) {
    switch (type) {
        case NpcType::Orc: return 20;
        case NpcType::Squirrel: return 5;
        case NpcType::Druid: return 10;
        case NpcType::Knight: return 30;
        case NpcType::Elf: return 10;
        case NpcType::Dragon: return 50;
        case NpcType::Bear: return 5;
        case NpcType::Robber: return 10;
        case NpcType::Werewolf: return 40;
        case NpcType::Princess: return 1;
        case NpcType::Toad: return 1;
        case NpcType::Slaver: return 10;
        case NpcType::Pegasus: return 30;
        case NpcType::Bittern: return 50;
        case NpcType::Desman: return 5;
        case NpcType::Bull: return 30;
        default: return 10;
    }
}

int NPCFactory::getKillDistance(NpcType type) {
    switch (type) {
        case NpcType::Orc: return 10;
        case NpcType::Squirrel: return 5;
        case NpcType::Druid: return 10;
        case NpcType::Knight: return 10;
        case NpcType::Elf: return 50;
        case NpcType::Dragon: return 30;
        case NpcType::Bear: return 10;
        case NpcType::Robber: return 10;
        case NpcType::Werewolf: return 5;
        case NpcType::Princess: return 1;
        case NpcType::Toad: return 10;
        case NpcType::Slaver: return 10;
        case NpcType::Pegasus: return 10;
        case NpcType::Bittern: return 10;
        case NpcType::Desman: return 20;
        case NpcType::Bull: return 10;
        default: return 10;
    }
}