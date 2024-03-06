#include "../header/Dragon.h"

bool DragonVisitor::visit(const std::shared_ptr<Knight>& attacker) const {
    return 0;
}

bool DragonVisitor::visit(const std::shared_ptr<Dragon>& attacker) const {
    return 0;
}

bool DragonVisitor::visit(const std::shared_ptr<Pegasus>& attacker) const {
    return 1;
}

Dragon::Dragon(std::string hName, short int x, short int y) : Heroes(DRAGON, hName, x, y) {}

Dragon::Dragon(std::istream & is) : Heroes(DRAGON, is) {}

void Dragon::print()
{
    std::cout << *this;
}

void Dragon::save(std::ostream & os)
{
    os << DRAGON << std::endl;
    Heroes::save(os);
}

std::ostream & operator<<(std::ostream & os, Dragon & dr)
{
    os << "Dragon: " << *static_cast<Heroes*> (&dr) << std::endl;
    return os;
}

int Dragon::accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker)
{
    std::shared_ptr<const Heroes> npc_const_ptr = shared_from_this();
    std::shared_ptr<Heroes> npc_ptr = std::const_pointer_cast<Heroes>(npc_const_ptr);
    std::shared_ptr<Dragon> defender = std::dynamic_pointer_cast<Dragon>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fightNotify(defender, result);

    return result;
}
