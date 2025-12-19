#include "../../include/npc/bear.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Bear::Bear(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Bear, 5, 10) {
}

bool Bear::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Bear>(shared_from_this()));
}

std::string Bear::getTypeName() const {
    return "Bear";
}