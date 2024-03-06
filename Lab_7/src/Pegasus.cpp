#include "../header/Pegasus.h"

bool PegasusVisitor::visit(const std::shared_ptr<Knight>& attacker) const {
    return 0;
}

bool PegasusVisitor::visit(const std::shared_ptr<Dragon>& attacker) const {
    return 0;
}

bool PegasusVisitor::visit(const std::shared_ptr<Pegasus>& attacker) const {
    return 0;
}

Pegasus::Pegasus(std::string hName, short int x, short int y) : Heroes(PEGASUS, hName, x, y, RANGE_ATTACK_WF, RANGE_MOVE_WF) {}

Pegasus::Pegasus(std::istream & is) : Heroes(PEGASUS ,is) 
{
    _rangeAttack = RANGE_ATTACK_WF;
    _rangeMove = RANGE_MOVE_WF;
}

void Pegasus::print()
{
    std::cout << *this;
}

void Pegasus::save(std::ostream & os)
{
    os << PEGASUS << std::endl;
    Heroes::save(os);
}

std::ostream & operator<<(std::ostream & os, Pegasus & wf)
{
    os << "Pegasus: " << *static_cast<Heroes*> (&wf) << std::endl;
    return os;
}

int Pegasus::accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker)
{
    std::shared_ptr<const Heroes> npc_const_ptr = shared_from_this();
    std::shared_ptr<Heroes> npc_ptr = std::const_pointer_cast<Heroes>(npc_const_ptr);
    std::shared_ptr<Pegasus> defender = std::dynamic_pointer_cast<Pegasus>(npc_ptr);

    bool result = attacker_visitor->visit(defender);
    
    if (result) {
        int pointAttacker = throwTheDice();
        int pointDefender = throwTheDice();
        if (pointAttacker <= pointDefender) {
            result = false;
        }
    } 
    attacker->fightNotify(defender, result);

    return result;
}
