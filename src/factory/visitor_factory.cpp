#include "../../include/factory/visitor_factory.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/squirrel.h"
#include "../../include/npc/druid.h"
#include "../../include/npc/knight.h"
#include "../../include/npc/elf.h"
#include "../../include/npc/dragon.h"
#include "../../include/npc/bear.h"
#include "../../include/npc/robber.h"
#include "../../include/npc/werewolf.h"
#include "../../include/npc/princess.h"
#include "../../include/npc/toad.h"
#include "../../include/npc/slaver.h"
#include "../../include/npc/pegasus.h"
#include "../../include/npc/bittern.h"
#include "../../include/npc/desman.h"
#include "../../include/npc/bull.h"

std::shared_ptr<BattleVisitor> VisitorFactory::createVisitor(const std::shared_ptr<NPC>& npc) {
    // Проверяем тип NPC и возвращаем соответствующий Visitor
    if (std::dynamic_pointer_cast<Orc>(npc)) {
        return std::make_shared<OrcVisitor>();
    } else if (std::dynamic_pointer_cast<Squirrel>(npc)) {
        return std::make_shared<SquirrelVisitor>();
    } else if (std::dynamic_pointer_cast<Druid>(npc)) {
        return std::make_shared<DruidVisitor>();
    } else if (std::dynamic_pointer_cast<Knight>(npc)) {
        return std::make_shared<KnightVisitor>();
    } else if (std::dynamic_pointer_cast<Elf>(npc)) {
        return std::make_shared<ElfVisitor>();
    } else if (std::dynamic_pointer_cast<Dragon>(npc)) {
        return std::make_shared<DragonVisitor>();
    } else if (std::dynamic_pointer_cast<Bear>(npc)) {
        return std::make_shared<BearVisitor>();
    } else if (std::dynamic_pointer_cast<Robber>(npc)) {
        return std::make_shared<RobberVisitor>();
    } else if (std::dynamic_pointer_cast<Werewolf>(npc)) {
        return std::make_shared<WerewolfVisitor>();
    } else if (std::dynamic_pointer_cast<Princess>(npc)) {
        return std::make_shared<PrincessVisitor>();
    } else if (std::dynamic_pointer_cast<Toad>(npc)) {
        return std::make_shared<ToadVisitor>();
    } else if (std::dynamic_pointer_cast<Slaver>(npc)) {
        return std::make_shared<SlaverVisitor>();
    } else if (std::dynamic_pointer_cast<Pegasus>(npc)) {
        return std::make_shared<PegasusVisitor>();
    } else if (std::dynamic_pointer_cast<Bittern>(npc)) {
        return std::make_shared<BitternVisitor>();
    } else if (std::dynamic_pointer_cast<Desman>(npc)) {
        return std::make_shared<DesmanVisitor>();
    } else if (std::dynamic_pointer_cast<Bull>(npc)) {
        return std::make_shared<BullVisitor>();
    }
    
    // Если тип неизвестен, возвращаем nullptr или базовый Visitor
    return nullptr;
}