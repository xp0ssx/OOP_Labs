#include "point.h"

Point::Point() : _x(0), _y(0) {}

Point::Point(double newX, double newY) : _x(newX), _y(newY) {}

Point::Point(const Point &other) : _x(other._x), _y(other._y) {}

Point::~Point() {}

bool Point::operator == (const Point &other) const {
    return this->distance(other) < EPSILON ? true : false;
}

bool Point::operator != (const Point &other) const {
    return !(*this == other);
}

std::istream& operator >> (std::istream& is, Point& point) {
    is >> point._x; is >> point._y;
    return is;
}

std::ostream& operator << (std::ostream &os, const Point& point) {
    return os << "x = " << point._x << ", y = " << point._y << std::endl;
}

double Point::getX() const {
    return _x;
}

double Point::getY() const {
    return _y;
}

double Point::distance(const Point &other) const {
    return pow((pow(_x - other._x, 2) + pow(_y - other._y, 2)), 0.5);
}

Point &Point::operator=(const Point &other) {
    _y = other._y;
    _x = other._x;
    return *this;
}

Point getAv(const std::vector<Point> &p) {
    double sumX=0, sumY=0;
    for (size_t i = 0; i < p.size(); i++) {
        sumX += p[i].getX();
        sumY += p[i].getY();
    }
    return Point(sumX / p.size(), sumY / p.size());
}

