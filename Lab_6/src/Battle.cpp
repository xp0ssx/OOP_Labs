#include "../header/Battle.h"
#include "../header/FactoryHeroes.h"

std::map<HeroesClass, std::shared_ptr<Visitor>> visitors = {
    {KNIGHT, std::make_shared<KnightVisitor>()},
    {DRAGON, std::make_shared<DragonVisitor>()},
    {PEGASUS, std::make_shared<PegasusVisitor>()}
};

set_t battle(const set_t & array)
{
    set_t dead_list;

    for (const auto& attacker : array) {
        for (const auto& defender : array) {
            if (attacker != defender && attacker->isClose(defender) && dead_list.find(defender) == dead_list.end()) {
                bool win = defender->accept(visitors[attacker->getType()], attacker);
                if (win) {
                    dead_list.insert(defender);
                }
            }
        }
    }

    return dead_list;
}

std::ostream & operator<<(std::ostream & os, const set_t & array)
{
    for (auto & n : array) {
        n->print();
    }

    return os;
}

void save(const set_t & array, const std::string & filename)
{
    std::ofstream fs(filename);

    fs << array.size() << std::endl;

    for (auto & n : array) {
        n->save(fs);
    }

    fs.flush();
    fs.close();
}

set_t load(const std::string & filename)
{
    set_t res;
    std::ifstream is(filename);
    Factory fac;

    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) {
            res.insert(fac.createHero(is));
        }

        is.close();
    } else {
        throw std::invalid_argument("Error! load : file is not correctly");
    }

    return res;
}
