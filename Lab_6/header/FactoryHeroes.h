#pragma once

#include "Knight.h"
#include "Pegasus.h"
#include "Dragon.h"
#include "Observer.h"
 
#include <cstdlib>

class Factory
{
public:
    std::shared_ptr<Heroes> createHero(HeroesClass hClass, short int x, short int y);
    std::shared_ptr<Heroes> createHero(std::istream & is);
};
