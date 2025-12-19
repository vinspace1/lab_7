#pragma once

#include "npc.h"

class Bear : public NPC {
public:
    Bear(int x, int y, const std::string& name);
    bool accept(const std::shared_ptr<BattleVisitor>& attacker) override;
    std::string getTypeName() const override;
};