#pragma once

#include "npc.h"

class Slaver : public NPC {
public:
    Slaver(int x, int y, const std::string& name);
    bool accept(const std::shared_ptr<BattleVisitor>& attacker) override;
    std::string getTypeName() const override;
};