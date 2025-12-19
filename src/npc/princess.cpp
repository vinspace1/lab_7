#include "../../include/npc/princess.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Princess::Princess(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Princess, 1, 1) {
}

bool Princess::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Princess>(shared_from_this()));
}

std::string Princess::getTypeName() const {
    return "Princess";
}