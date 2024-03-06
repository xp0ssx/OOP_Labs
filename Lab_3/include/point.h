#include <iostream>
#include <vector>
#include <cmath>
#define EPSILON 0.01
#define PI 3.141592653
#ifndef POINT_H
#define POINT_H

class Point final {
    friend std::ostream& operator << (std::ostream &os, const Point& point);
    friend std::istream& operator >> (std::istream& is, Point& point);
    public :
        Point();
        Point(const double newX, const double newY);
        Point(const Point &other);
        virtual ~Point();
        bool operator == (const Point &other) const;
        bool operator != (const Point &other) const;
        double getX() const;
        double getY() const;
        double distance(const Point &other) const;
        Point &operator=(const Point &other);
        friend Point getAv(const std::vector<Point> &p);
    private:
        double _x;
        double _y;
};

#endif 