#pragma once

#include <map>

#include "FactoryHeroes.h"

set_t battle(const set_t & array);
std::ostream & operator<<(std::ostream & os, const set_t & array);
void save(const set_t & array, const std::string & filename);
set_t load(const std::string & filename);
