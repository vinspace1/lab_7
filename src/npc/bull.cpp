#include "../../include/npc/bull.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Bull::Bull(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Bull, 30, 10) {
}

bool Bull::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Bull>(shared_from_this()));
}

std::string Bull::getTypeName() const {
    return "Bull";
}