#pragma once

#include "Heroes.h"

#define RANGE_ATTACK_SQ 5
#define RANGE_MOVE_SQ 5

struct KnightVisitor : public Visitor 
{
    bool visit(const std::shared_ptr<Pegasus>&) const override;
    bool visit(const std::shared_ptr<Dragon>&) const override;
    bool visit(const std::shared_ptr<Knight>&) const override;
};  

class Knight final : public Heroes {
public:
    Knight(std::string hName, short int x, short int y);
    Knight(std::istream & is);

    void print() override;
    void save(std::ostream & os) override;
    friend std::ostream & operator<<(std::ostream & os, Knight & sq);
    virtual int accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<Heroes>& attacker) override;
};
