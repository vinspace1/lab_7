#include "../../include/npc/pegasus.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Pegasus::Pegasus(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Pegasus, 30, 10) {
}

bool Pegasus::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Pegasus>(shared_from_this()));
}

std::string Pegasus::getTypeName() const {
    return "Pegasus";
}