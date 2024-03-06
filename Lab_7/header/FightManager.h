#pragma once

#include <queue>
#include <shared_mutex>
#include <optional>
#include <thread>

#include "Battle.h"

#define MAX_TIME 30

using namespace std::chrono_literals;

inline int _timer = 0;


struct FightEvent
{
    std::shared_ptr<Heroes> attacker;
    std::shared_ptr<Heroes> defender;
};

class FightManager 
{
public:
    FightManager() = default;

    static FightManager & get();
    void addEvent(FightEvent && event);
    void operator()();

private:
    std::queue<FightEvent> _events;
    std::shared_mutex _mtx;
};
