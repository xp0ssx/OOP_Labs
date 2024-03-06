#pragma once

#include "Heroes.h"

#define RANGE_ATTACK_DR 10
#define RANGE_MOVE_DR 10

struct DragonVisitor : public Visitor
{
    bool visit(const std::shared_ptr<Pegasus>&) const override;
    bool visit(const std::shared_ptr<Dragon>&) const override;
    bool visit(const std::shared_ptr<Knight>&) const override;
};


class Dragon final : public Heroes {
public:
    Dragon(std::string hName, short int x, short int y);
    Dragon(std::istream & is);

    void print() override;
    void save(std::ostream & os) override;
    friend std::ostream & operator<<(std::ostream & os, Dragon & dr);
    virtual int accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker) override;
};  
