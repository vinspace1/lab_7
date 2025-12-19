#include "../../include/npc/werewolf.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Werewolf::Werewolf(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Werewolf, 40, 5) {
}

bool Werewolf::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Werewolf>(shared_from_this()));
}

std::string Werewolf::getTypeName() const {
    return "Werewolf";
}