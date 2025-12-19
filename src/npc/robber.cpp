#include "../../include/npc/robber.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Robber::Robber(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Robber, 10, 10) {
}

bool Robber::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Robber>(shared_from_this()));
}

std::string Robber::getTypeName() const {
    return "Robber";
}