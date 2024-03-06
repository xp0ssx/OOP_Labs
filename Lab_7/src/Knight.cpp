#include "../header/Knight.h"

bool KnightVisitor::visit(const std::shared_ptr<Knight>& attacker) const {
    return 0;
}

bool KnightVisitor::visit(const std::shared_ptr<Dragon>& attacker) const {
    return 1;
}

bool KnightVisitor::visit(const std::shared_ptr<Pegasus>& attacker) const {
    return 0;
}

Knight::Knight(std::string hName, short int x, short int y) : Heroes(KNIGHT, hName, x, y, RANGE_ATTACK_SQ, RANGE_MOVE_SQ) {}

Knight::Knight(std::istream & is) : Heroes(KNIGHT, is)
{
    _rangeAttack = RANGE_ATTACK_SQ;
    _rangeMove = RANGE_MOVE_SQ;
}

void Knight::print()
{
    std::cout << *this;
}

void Knight::save(std::ostream & os)
{
    os << KNIGHT << std::endl;
    Heroes::save(os);
}

std::ostream & operator<<(std::ostream & os, Knight & sq)
{
    os << "Knight: " << *static_cast<Heroes*> (&sq) << std::endl;
    return os;
}

int Knight::accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker)
{
    std::shared_ptr<const Heroes> npc_const_ptr = shared_from_this();
    std::shared_ptr<Heroes> npc_ptr = std::const_pointer_cast<Heroes>(npc_const_ptr);
    std::shared_ptr<Knight> defender = std::dynamic_pointer_cast<Knight>(npc_ptr);
    
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
