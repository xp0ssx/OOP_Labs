#include "../header/Heroes.h"

std::string getRandNameKn()
{
    std::string hName = KnightName[(std::rand()) % 10];
    
    return hName;
}

std::string getRandNamePg()
{
    std::string hName = PegasusName[(std::rand()) % 10];
    
    return hName;
}

std::string getRandNameDr()
{
    std::string hName = DragonName[(std::rand()) % 10];
    
    return hName;
}

int throwTheDice()
{   
    return (rand() % 6) + 1;
}

Heroes::Heroes(HeroesClass hClass, std::string hName, int x, int y, int rA, int rM) :
    _type(hClass), _name(hName), _x(x), _y(y), _rangeAttack(rA), _rangeMove(rM) {}

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
    std::lock_guard<std::mutex> lck(mtx);
    return _type;
}

std::pair<int, int> Heroes::position()
{
    std::lock_guard<std::mutex> lck(mtx);
    return {_x, _y};
}

int Heroes::getRangeMove() const
{
    return _rangeMove;
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

bool Heroes::isClose(const std::shared_ptr<Heroes> & other)
{
    std::lock_guard<std::mutex> lck(mtx);
    
    if (std::pow(_x - other->_x, 2) + std::pow(_y - other->_y, 2) <= std::pow(_rangeAttack, 2)) {
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

void Heroes::move(int shiftX, int shiftY, int maxX, int maxY)
{
    std::lock_guard<std::mutex> lck(mtx);

    if ((_x + shiftX >= 0) && (_x + shiftX <= maxX)) {
        _x += shiftX;
    }

    if ((_y + shiftY >= 0) && (_y + shiftY <= maxY)) {
        _y += shiftY;
    }
}

bool Heroes::isAlive()
{
    std::lock_guard<std::mutex> lck(mtx);
    return _alive;
}

void Heroes::mustDie()
{
    std::lock_guard<std::mutex> lck(mtx);
    _alive = false;
}
