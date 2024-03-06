#pragma once
#include <iostream>
#include <cmath>
#include <array.h>
#define EPSILON 0.01
#define PI 3.141592653

template <typename T>
class Point {
    friend std::ostream& operator << (std::ostream& os, const Point<T> &point) {
        return os << "(" << point._x << ", " << point._y << ")";
    }
    friend std::istream& operator >> (std::istream& is, const Point<T> &point) {
        is >> point._x; is >> point._y;
        return is;
    }
    friend Point<T> getAv(const Array<Point<T>> &p) {
        T sumX=0, sumY=0;
        for (size_t i = 0; i < p.size(); i++) {
            sumX += p[i].getX();
            sumY += p[i].getY();
        }
        return Point(sumX / p.size(), sumY / p.size());
    }
    public :
        Point();
        Point(const T &newX, const T &newY);
        Point(const Point &other);
        virtual ~Point() noexcept;
        bool operator == (const Point<T> &other) const;
        bool operator != (const Point<T> &other) const;
        Point<T> &operator=(const Point<T> &other);
        T getX() const;
        T getY() const;
        double distance(const Point &other) const;
    private:
        T _x;
        T _y;
};