#include "figure.h"
#include <cmath>
#ifndef OCTAGON_H
#define OCTAGON_H

class Octagon final: public Figure {
    public:
        Octagon();
        Octagon(const std::vector<Point> & points);
        Octagon(const Octagon & other);
        Octagon(const Octagon &&other);
        virtual ~Octagon() noexcept = default;
        operator double() const override;
        Point getCenter() const override;
        Octagon &operator=(const Octagon &other);
        Octagon &operator=(const Octagon &&other);
    private:
        bool isEqual(const Figure &other) const override;
        bool valid(const std::vector<Point> &p) const override;
        void print(std::ostream &os) const override;
        void input(std::istream &os) override;
};

#endif