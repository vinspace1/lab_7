#pragma once

#include "../visitor/battle_visitor.h"
#include "../npc/npc.h"
#include <memory>

class VisitorFactory {
public:
    static std::shared_ptr<BattleVisitor> createVisitor(const std::shared_ptr<NPC>& npc);
};