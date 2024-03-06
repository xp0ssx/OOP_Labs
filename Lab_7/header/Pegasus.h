#pragma once

#include "Heroes.h"

#define RANGE_ATTACK_WF 5
#define RANGE_MOVE_WF 40

struct PegasusVisitor : public Visitor 
{
    bool visit(const std::shared_ptr<Pegasus>&) const override;
    bool visit(const std::shared_ptr<Dragon>&) const override;
    bool visit(const std::shared_ptr<Knight>&) const override;
};  

class Pegasus : public Heroes {
public:
    Pegasus(std::string hName, short int x, short int y);
    Pegasus(std::istream & is);

    void print() override;
    void save(std::ostream & os) override;
    friend std::ostream & operator<<(std::ostream & os, Pegasus & wf);
    virtual int accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker) override;
};
