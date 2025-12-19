#pragma once

#include "npc.h"

class Toad : public NPC {
public:
    Toad(int x, int y, const std::string& name);
    bool accept(const std::shared_ptr<BattleVisitor>& attacker) override;
    std::string getTypeName() const override;
};