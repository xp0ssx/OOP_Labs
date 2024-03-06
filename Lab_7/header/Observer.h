#pragma once

#include "Heroes.h"

class TextObserver final : public IFightObserver
{
public:
    TextObserver() = default;
    ~TextObserver() = default;

    static std::shared_ptr<IFightObserver> get();
    void onFight(const std::shared_ptr<Heroes> attacker, const std::shared_ptr<Heroes> defender, bool win) override;
};

class FileObserver final : public IFightObserver
{
public:
    FileObserver() = default;
    ~FileObserver() = default;

    static std::shared_ptr<IFightObserver> get();
    void onFight(const std::shared_ptr<Heroes> attacker, const std::shared_ptr<Heroes> defender, bool win) override;
};
