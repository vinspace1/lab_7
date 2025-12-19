#include "../../include/npc/desman.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Desman::Desman(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Desman, 5, 20) {
}

bool Desman::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Desman>(shared_from_this()));
}

std::string Desman::getTypeName() const {
    return "Desman";
}