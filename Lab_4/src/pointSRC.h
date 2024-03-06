#pragma once
#include "point.h"

template <typename T>
Point<T>::Point() : _x(), _y() {}

template <typename T>
Point<T>::Point(const T &newX, const T &newY) : _x(newX), _y(newY) {}

template <typename T>
Point<T>::Point(const Point<T> &other) : _x(other._x), _y(other._y) {}

template <typename T>
Point<T>::~Point() noexcept{}

template <typename T>
bool Point<T>::operator == (const Point<T> &other) const {
    return this->distance(other) < EPSILON ? true : false;
}

template <typename T>
bool Point<T>::operator != (const Point<T> &other) const {
    return !(*this == other);
}

template <typename T>
T Point<T>::getX() const {
    return _x;
}

template <typename T>
T Point<T>::getY() const {
    return _y;
}

template <typename T>
double Point<T>::distance(const Point &other) const {
    return pow((pow(_x - other._x, 2) + pow(_y - other._y, 2)), 0.5);
}

template <typename T>
Point<T> &Point<T>::operator=(const Point<T> &other) {
    _y = other._y;
    _x = other._x;
    return *this;
}