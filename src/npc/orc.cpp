#include "../../include/npc/orc.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Orc::Orc(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Orc, 20, 10) {
}

bool Orc::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Orc>(shared_from_this()));
}

std::string Orc::getTypeName() const {
    return "Orc";
}