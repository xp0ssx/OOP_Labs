#include "../header/FightManager.h"

FightManager & FightManager::get()
{
    static FightManager inst;
    
    return inst;
}

void FightManager::addEvent(FightEvent && event)
{
    std::lock_guard<std::shared_mutex> lock(_mtx);
    _events.push(event);
}

std::map<HeroesClass, std::shared_ptr<Visitor>> visitors = {
    {DRAGON, std::make_shared<DragonVisitor>()},
    {KNIGHT, std::make_shared<KnightVisitor>()},
    {PEGASUS, std::make_shared<PegasusVisitor>()}
};

void FightManager::operator()()
{
    while(_timer != MAX_TIME) {
        std::optional<FightEvent> event;
        {
            std::lock_guard<std::shared_mutex> lock(_mtx);
            if (!_events.empty()) {
                event = _events.back();
                _events.pop();
            }
        }
        
        if (event) {
            if (event->attacker->isAlive()) {
                if (event->defender->isAlive()) {
                    if (event->defender->accept(visitors[event->attacker->getType()], event->attacker)) {
                        event->defender->mustDie();
                    }
                }
            }
        }
        
    }
}
