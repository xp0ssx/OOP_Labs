#include <random>
#include <chrono>

#include "header/FightManager.h"

std::mutex printMtx;

int main()
{
    srand(time(nullptr));

    const int MAX_X{100};
    const int MAX_Y{100};

    set_t array;
    Factory fact;
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i) {
        array.insert(fact.createHero(
            HeroesClass(std::rand() % 3),
            std::rand() % MAX_X, 
            std::rand() % MAX_Y)
            );
    }

    std::cout << "Starting list:" << std::endl
              << array;

    std::cout.flush();

    std::thread fightThread(std::ref(FightManager::get()));
    std::thread moveThread([&array, MAX_X, MAX_Y]()
    {
        while (_timer == MAX_TIME) {
            for (std::shared_ptr<Heroes> npc : array) {
                if (npc->isAlive()) {
                    int randNumbMinX = (std::rand() % 2) * 2 - 1;
                    int randNumbMinY = (std::rand() % 2) * 2 - 1;

                    int distance = std::rand() % npc->getRangeMove();

                    int shiftX = distance * randNumbMinX;
                    int shiftY = (npc->getRangeMove() - distance) * randNumbMinY;

                    npc->move(shiftX, shiftY, MAX_X, MAX_Y);
                }
            }

            for (std::shared_ptr<Heroes> npc : array) {
                for (std::shared_ptr<Heroes> other : array) {
                    if (other != npc) {
                        if (npc->isAlive()) {
                            if(other->isAlive()) {
                                if (npc->isClose(other)) {
                                    FightManager::get().addEvent({npc, other});
                                }
                            }
                        }
                    }
                }
            }

            std::this_thread::sleep_for(717ms);
        }
        
    });

    while (_timer == MAX_TIME) {
        const int grid{20}, stepX{MAX_X / grid}, stepY{MAX_Y / grid};
        {
            std::array<char, grid * grid> playfields{0};
            
            for (std::shared_ptr<Heroes> npc : array) {
                auto [x, y] = npc->position();

                int i = x / stepX;
                int j = y / stepY;

                if (npc->isAlive()) {
                    switch (npc->getType()) {
                    case HeroesClass::KNIGHT:
                        playfields[i + grid * j] = 'S';
                        break;
                    case HeroesClass::PEGASUS:
                        playfields[i + grid * j] = 'W';
                        break;
                    case HeroesClass::DRAGON:
                        playfields[i + grid * j] = 'D';
                        break;
                    default:
                        break;
                    }
                } else {
                    playfields[i + grid * j] = '+';
                }
            }

            std::lock_guard<std::mutex> lck(printMtx);
            
            for (size_t i = 0; i < grid; ++i) {
                for (size_t j = 0; j < grid; ++j) {
                    char square = playfields[i + j * grid];

                    if (square != 0) {
                        std::cout << "[" << square << "]";
                    } else {
                        std::cout << "[ ]";
                    }
                }
                std::cout << std::endl;
            }
            std::cout.flush();
            std::cout << std::endl; 
        }

        std::this_thread::sleep_for(1s);
        _timer++;
    }

    fightThread.join();
    moveThread.join();

    std::cout << "Survivors: \n" << array;
    std::cout.flush();

    return 0;
}
