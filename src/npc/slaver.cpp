#include "../../include/npc/slaver.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Slaver::Slaver(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Slaver, 10, 10) {
}

bool Slaver::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Slaver>(shared_from_this()));
}

std::string Slaver::getTypeName() const {
    return "Slaver";
}