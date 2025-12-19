#pragma once

#include "npc.h"

class Robber : public NPC {
public:
    Robber(int x, int y, const std::string& name);
    bool accept(const std::shared_ptr<BattleVisitor>& attacker) override;
    std::string getTypeName() const override;
};