#pragma once
#include "figure.h"

template <typename T>
Figure<T>::Figure() {
    Array<Point<T>> _points;
}

template <typename T>
Figure<T>::Figure(const Figure<Point<T>> &other) : _points(other._points) {}

template <typename T>
Figure<T>::Figure(Figure<Point<T>> &&other) noexcept {
    std::swap(this->_points, other._points);
}

template <typename T>
Array<Point<T>> Figure<T>::getPoints() const {
    return _points;
}

template <typename T>
Figure<T>::Figure(const std::initializer_list<Point<T>> &list) : _points(list) {}

