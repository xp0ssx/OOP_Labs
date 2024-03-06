#include "./header/Battle.h"
#include <random>
#include <chrono>
#include <thread>
#include "./header/FactoryHeroes.h"

int main()
{
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::cout << "Generating ..." << std::endl;

    set_t arr;
    Factory fact;

    for (size_t i = 0; i < 30; ++i) {
        HeroesClass r = static_cast<HeroesClass>((rnd() % 3) + 1);
        arr.insert(fact.createHero(r, rnd() % 500, rnd() % 500));
    }

    std::cout << "Saving ..." << std::endl;
    save(arr, "./npc.txt");

    std::cout << "Loading ..." << std::endl;
    arr = load("./npc.txt");

    std::cout<<"Fight    \n\n\n\n";
    for (size_t dist = DISTANCE_FIGHT; (dist <= 1000) && !(arr.empty()); dist += 50) {
        auto kb = battle(arr);

        for (auto & d : kb) {
            arr.erase(d);
        }

        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << DISTANCE_FIGHT << std::endl
                  << "killed: " << kb.size() << "\n\n\n";
    }

    std::cout << "Survivors: " << arr;

    return 0;
}
