#include "../header/Heroes.h"

std::string getRandNameKn()
{
    std::srand(std::time(nullptr));
    std::string hName = KnightName[(std::rand()) % 10];
    
    return hName;
}

std::string getRandNamePg()
{
    std::srand(std::time(nullptr));
    std::string hName = PegasusName[(std::rand()) % 10];
    
    return hName;
}

std::string getRandNameDr()
{
    std::srand(std::time(nullptr));
    std::string hName = DragonName[(std::rand()) % 10];
    
    return hName;
}

Heroes::Heroes(HeroesClass hClass, std::string hName, short int x, short int y) :
    _type(hClass), _name(hName), _x(x), _y(y) {}

Heroes::Heroes(HeroesClass t, std::istream & is) : _type(t)
{
    is >> _x;
    is >> _y;
    is >> _name;
}

std::string Heroes::getName() const
{
    return _name;
}

HeroesClass & Heroes::getType() 
{
    return _type;
}

void Heroes::subscribe(std::shared_ptr<IFightObserver> observer)
{
    _obs.push_back(observer);
}

void Heroes::fightNotify(const std::shared_ptr<Heroes> defender, bool win)
{
    for (auto& o : _obs) {
        o->onFight(shared_from_this(), defender, win);
    }
}

bool Heroes::isClose(const std::shared_ptr<Heroes> & other) const
{
    if (std::pow(_x - other->_x, 2) + std::pow(_y - other->_y, 2) <= std::pow(DISTANCE_FIGHT, 2)) {
        return true;
    } else {
        return false;
    }
}

void Heroes::save(std::ostream & os)
{
    os << _x << " ";
    os << _y << " ";
    os << _name << std::endl;
}

std::ostream & operator<<(std::ostream & os, Heroes & heroes)
{
    os << heroes._name <<
        " is located {" <<  heroes._x << " " << heroes._y << "}" << std::endl;

    return os;
}
