#pragma once
#include "triangle.h"

template <typename T>
Triangle<T>::Triangle(): Figure<T>::Figure<T>() {}

template <typename T>
Triangle<T>::Triangle(const Triangle<Point<T>> &other): Figure<T>::Figure<T>(other) {}

template <typename T>
Triangle<T>::Triangle(Triangle<Point<T>> &&other) noexcept: Figure<T>::Figure<T>(other) {}

template <typename T>
Triangle<T>::Triangle(const std::initializer_list<Point<T>> &list) {
    const Array<Point<T>> tmp(list);
    if (list.size() != Figures::Triangle) {
        throw std::range_error("invalid number of coordinates");
    } else if (!valid(tmp)){
        throw std::range_error("Error! Triangle Constructor: invalid points");
    } else {
        Array<Point<T>> tmp(list);
        Figure<T>::_points = list;
    }
}

template <typename T>
Triangle<T>::Triangle(const Array<Point<T>> &arr) {
    if (arr.size() != Figures::Triangle) {
        throw std::range_error("invalid number of coordinates");
    } else if (!valid(arr)){
        throw std::range_error("Error! Hexagon Constructor: invalid points");
    } else {
        Figure<T>::_points = arr;
    }
}

template <typename T>
bool Triangle<T>::valid(const Array<Point<T>> &list) {
    Array<Point<T>> tmp(list);
    double l1 = tmp[0].distance(tmp[1]), l2 = tmp[0].distance(tmp[2]), l3 = tmp[0].distance(tmp[2]);
    return fabs(l1 - l2) < EPSILON && fabs(l2 - l3) < EPSILON && fabs(l1 - l3) < EPSILON;
}

template <typename T>
Point<T> Triangle<T>::getCenter() const {
    if (Figure<T>::_points.size() == 0) {
        throw std::range_error("can't get center of empty");
    }
    Point<T> tmp = getAv(Figure<T>::_points);
    return tmp;
}

template <typename T>
Triangle<T>::operator double() const {
    if (Figure<T>::_points.size() == 0) {
        throw std::range_error("can't get square of empty");
    }
    return std::pow((Figure<T>::_points[0]).distance((Figure<T>::_points[1])), 2) * std::pow(3,0.5) / 4;
}

template <typename T>
bool Triangle<T>::operator ==(const Figure<T> &other) const{
    const Triangle<T> *ptr = static_cast<const Triangle<T>*>(&other);
    if (ptr) {
        return (Figure<T>::_points[0]).distance((Figure<T>::_points[1])) == (other.getPoints()[0]).distance((other.getPoints()[1]));
    } else {
        return false;
    }
}

template <typename T>
Triangle<T> &Triangle<T>::operator = (Figure<T> &other) {
    Triangle<T> *ptr = static_cast<const Triangle<T>*>(&other);
    if (ptr) {
        Figure<T>::_points = other._points;
        return *this;
    } else {
        throw std::logic_error("can't assign different types of figures");
    }
}