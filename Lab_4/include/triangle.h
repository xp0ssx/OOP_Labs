#pragma once
#include "figure.h"

template <typename T>
class Triangle: public Figure<T> {
    friend std::ostream& operator << (std::ostream& os, const Triangle<T> &fig) {
        os << "Triangle\n" << fig._points;
        return os;
    }
    friend std::istream& operator >> (std::istream& is, const Triangle<T> &fig) {
        Array<Point<T>> tmpV;
        Point<T> tmp;
        for (size_t i = 0; i < Figures::Triangle; ++i) {
            is >> tmp;
            tmpV.push_back(tmp);
        }
        if (!valid(tmpV)) {
            throw std::range_error("Error! Square Constructor: invalid points");
        } else {
            Figure<T>::_points = tmpV;
        }
        return is;
    }
    public:
        Triangle();
        Triangle(const std::initializer_list<Point<T>> &list);
        Triangle(const Triangle<Point<T>> &other);
        Triangle(Triangle<Point<T>> &&other) noexcept;
        Triangle(const Array<Point<T>> &arr);
        virtual ~Triangle() noexcept = default;

        Point<T> getCenter() const;
        operator double() const;

        bool operator==(const Figure<T> &other) const;
        Triangle<T> &operator = (Figure<T> &other);
    private:
        bool valid(const Array<Point<T>> &list);
};
