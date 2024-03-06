#pragma once
#include "figure.h"

namespace {
    const double OCTAGON_CONST = 1 + pow(2, 0.5);
}

template <typename T>
class Octagon: public Figure<T> {
    friend std::ostream& operator << (std::ostream& os, const Octagon<T> &fig) {
        os << "Octagon\n" << fig._points;
        return os;
    }
    friend std::istream& operator >> (std::istream& is, const Octagon<T> &fig) {
        Array<Point<T>> tmpV;
        Point<T> tmp;
        for (size_t i = 0; i < Figures::Octagon; ++i) {
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
        Octagon();
        Octagon(const std::initializer_list<Point<T>> &list);
        Octagon(const Octagon<Point<T>> &other);
        Octagon(Octagon<Point<T>> &&other) noexcept;
        Octagon(const Array<Point<T>> &arr);
        virtual ~Octagon() noexcept = default;

        Point<T> getCenter() const;
        operator double() const;

        bool operator==(const Figure<T> &other) const;
        Octagon<T> &operator = (Figure<T> &other);
        Octagon<T> &operator = (Figure<T> &&other);

    private:
        bool valid(const Array<Point<T>> &list);
};
