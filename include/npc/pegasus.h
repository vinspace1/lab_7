#pragma once

#include "npc.h"

class Pegasus : public NPC {
public:
    Pegasus(int x, int y, const std::string& name);
    bool accept(const std::shared_ptr<BattleVisitor>& attacker) override;
    std::string getTypeName() const override;
};