#include "../../include/npc/bittern.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Bittern::Bittern(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Bittern, 50, 10) {
}

bool Bittern::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Bittern>(shared_from_this()));
}

std::string Bittern::getTypeName() const {
    return "Bittern";
}