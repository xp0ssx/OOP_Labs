#include "figure.h"
#include "point.h"
#include <cmath>
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle final: public Figure{
    public:
        Triangle();
        Triangle(const std::vector<Point> & points);
        Triangle(const Triangle & other);
        Triangle(const Triangle &&other);
        virtual ~Triangle() noexcept = default;
        operator double() const override;
        Point getCenter() const override;
        Triangle &operator=(const Triangle &other);
        Triangle &operator=(const Triangle &&other);
    private:
        bool isEqual(const Figure &other) const override;
        bool valid(const std::vector<Point> &p) const override;
        void print(std::ostream &os) const override;
        void input(std::istream &os) override;
};
#endif
