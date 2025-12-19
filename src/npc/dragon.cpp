#include "../../include/npc/dragon.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Dragon::Dragon(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Dragon, 50, 30) {
}

bool Dragon::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Dragon>(shared_from_this()));
}

std::string Dragon::getTypeName() const {
    return "Dragon";
}