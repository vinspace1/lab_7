#include "../../include/npc/knight.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Knight::Knight(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Knight, 30, 10) {
}

bool Knight::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Knight>(shared_from_this()));
}

std::string Knight::getTypeName() const {
    return "Knight";
}