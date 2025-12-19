#pragma once

#include <memory>

class Orc;
class Squirrel;
class Druid;
class Knight;
class Elf;
class Dragon;
class Bear;
class Robber;
class Werewolf;
class Princess;
class Toad;
class Slaver;
class Pegasus;
class Bittern;
class Desman;
class Bull;

class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    
    virtual bool visit(const std::shared_ptr<Orc>& orc) = 0;
    virtual bool visit(const std::shared_ptr<Squirrel>& squirrel) = 0;
    virtual bool visit(const std::shared_ptr<Druid>& druid) = 0;
    virtual bool visit(const std::shared_ptr<Knight>& knight) = 0;
    virtual bool visit(const std::shared_ptr<Elf>& elf) = 0;
    virtual bool visit(const std::shared_ptr<Dragon>& dragon) = 0;
    virtual bool visit(const std::shared_ptr<Bear>& bear) = 0;
    virtual bool visit(const std::shared_ptr<Robber>& robber) = 0;
    virtual bool visit(const std::shared_ptr<Werewolf>& werewolf) = 0;
    virtual bool visit(const std::shared_ptr<Princess>& princess) = 0;
    virtual bool visit(const std::shared_ptr<Toad>& toad) = 0;
    virtual bool visit(const std::shared_ptr<Slaver>& slaver) = 0;
    virtual bool visit(const std::shared_ptr<Pegasus>& pegasus) = 0;
    virtual bool visit(const std::shared_ptr<Bittern>& bittern) = 0;
    virtual bool visit(const std::shared_ptr<Desman>& desman) = 0;
    virtual bool visit(const std::shared_ptr<Bull>& bull) = 0;
};

// Visitor для Орка
class OrcVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Белки
class SquirrelVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Друида
class DruidVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Рыцаря
class KnightVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Эльфа
class ElfVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Дракона
class DragonVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Медведя
class BearVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Разбойника
class RobberVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Оборотня
class WerewolfVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Принцессы
class PrincessVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Жабы
class ToadVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Работорговца
class SlaverVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Пегаса
class PegasusVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Выпи
class BitternVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Выхухоля
class DesmanVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};

// Visitor для Быка
class BullVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
    bool visit(const std::shared_ptr<Knight>& knight) override;
    bool visit(const std::shared_ptr<Elf>& elf) override;
    bool visit(const std::shared_ptr<Dragon>& dragon) override;
    bool visit(const std::shared_ptr<Bear>& bear) override;
    bool visit(const std::shared_ptr<Robber>& robber) override;
    bool visit(const std::shared_ptr<Werewolf>& werewolf) override;
    bool visit(const std::shared_ptr<Princess>& princess) override;
    bool visit(const std::shared_ptr<Toad>& toad) override;
    bool visit(const std::shared_ptr<Slaver>& slaver) override;
    bool visit(const std::shared_ptr<Pegasus>& pegasus) override;
    bool visit(const std::shared_ptr<Bittern>& bittern) override;
    bool visit(const std::shared_ptr<Desman>& desman) override;
    bool visit(const std::shared_ptr<Bull>& bull) override;
};