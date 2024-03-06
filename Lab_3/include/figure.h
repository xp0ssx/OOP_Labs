#include <iostream>
#include <vector>
#include <ostream>
#include <cmath>
#include "point.h"
#ifndef FIGURE_H
#define FIGURE_H


class Figure {
    public :
        Figure();
        Figure(const Figure &other);
        Figure(const Figure &&other) noexcept;
        ~Figure() = default;
        std::vector<Point> getPoints() const;
        virtual operator double () const = 0;
        friend bool operator==(const Figure &lhs, const Figure &rhs);
        virtual Point getCenter() const = 0;
        friend std::ostream &operator << (std::ostream& os, const Figure& f);
        friend std::istream &operator >> (std::istream& is, Figure& f);
    protected:
        virtual bool isEqual(const Figure &other) const = 0;
        virtual bool valid(const std::vector<Point> &p) const = 0;
        virtual void print(std::ostream &os) const = 0;
        virtual void input(std::istream &os) = 0;
        std::vector<Point> _points;
};

#endif 