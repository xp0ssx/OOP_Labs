#include "figure.h"
#include <cmath>
#ifndef HEXAGON_H
#define HEXAGON_H

class Hexagon final: public Figure {
    public:
        Hexagon();
        Hexagon(const std::vector<Point> & points);
        Hexagon(const Hexagon & other);
        Hexagon(const Hexagon && other);
        virtual ~Hexagon() noexcept = default;
        Hexagon &operator=(const Hexagon &other);
        Hexagon &operator=(const Hexagon &&other);
        operator double() const override;
        Point getCenter() const override;
    private:
        bool isEqual(const Figure &other) const override;
        bool valid(const std::vector<Point> &p) const override;
        void print(std::ostream &os) const override;
        void input(std::istream &os) override;
};

#endif