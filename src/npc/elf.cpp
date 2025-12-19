#include "../../include/npc/elf.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Elf::Elf(int x, int y, const std::string& name)
    : NPC(x, y, name, NpcType::Elf, 10, 50) {
}

bool Elf::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::static_pointer_cast<Elf>(shared_from_this()));
}

std::string Elf::getTypeName() const {
    return "Elf";
}