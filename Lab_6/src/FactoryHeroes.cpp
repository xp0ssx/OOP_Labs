#include "../header/FactoryHeroes.h"


std::shared_ptr<Heroes> Factory::createHero(HeroesClass hClass, short int x, short int y) {
    std::string hName;
    std::shared_ptr<Heroes> res;
    switch (hClass) {
        case HeroesClass::KNIGHT:
            hName = getRandNameKn();
            res = std::make_shared<Knight>(hName, x, y);
            break;
        case HeroesClass::PEGASUS:
            hName = getRandNamePg();
            res = std::make_shared<Pegasus>(hName, x, y);
            break;
        case HeroesClass::DRAGON:
            hName = getRandNameDr();
            res = std::make_shared<Dragon>(hName, x, y);
            break;
        default:
            throw std::invalid_argument("Error! createHero to param : invalid HeroesClass");
            break;
    }

    if (res) {
        res->subscribe(TextObserver::get());
        res->subscribe(FileObserver::get());
    }

    return res;
}

std::shared_ptr<Heroes> Factory::createHero(std::istream & is) {
    int hClass{0};
    std::shared_ptr<Heroes> res;
    if (is >> hClass) {
        switch (hClass) {
            case KNIGHT:
                res = std::make_shared<Knight>(is);
                break;
            case PEGASUS:
                res = std::make_shared<Pegasus>(is);
                break;
            case DRAGON:
                res = std::make_shared<Dragon>(is);
                break;
            default:
                throw std::invalid_argument("Error! createHero to file : invalid HeroesClass");
                break;
        }
    } else {
        std::cout <<"Huy\n";
        throw std::invalid_argument("Error! createHero to file : invalid enter into file");
    }

    if (res) {
        res->subscribe(TextObserver::get());
        res->subscribe(FileObserver::get());
    }

    return res;
}
