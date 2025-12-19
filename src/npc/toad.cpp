#include "../../include/npc/toad.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Toad::Toad(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Toad, 1, 10) {
}

bool Toad::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Toad>(shared_from_this()));
}

std::string Toad::getTypeName() const {
    return "Toad";
}