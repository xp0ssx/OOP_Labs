#include "../header/Observer.h"

std::shared_ptr<IFightObserver> TextObserver::get()
{
    static TextObserver instance;
    
    return std::shared_ptr<IFightObserver> (&instance, [](IFightObserver* ) {}); 
}

void TextObserver::onFight(const std::shared_ptr<Heroes> attacker, const std::shared_ptr<Heroes> defender, bool win)
{
    if (win) {
        std::cout << "\n\tMurder - - - - - - - - -\n";
        std::cout << "Killer - ";
        attacker->print();
        std::cout << "Victim - ";
        defender->print();
    } 
}

std::shared_ptr<IFightObserver> FileObserver::get()
{
    static FileObserver instance;

    return std::shared_ptr<IFightObserver> (&instance, [](IFightObserver* ){});
}

void FileObserver::onFight(const std::shared_ptr<Heroes> attacker, const std::shared_ptr<Heroes> defender, bool win)
{
    std::fstream file;
    file.open("./log.txt", std::ios::app);

    if (win) {
        file << "\n\tMurder - - - - - - - - -\n";
        file << (*attacker);
        file << (*defender);
        file.flush();
    } 
    
    file.close();
}
