#pragma once
#include "figure.h"

template <typename T>
class Hexagon: public Figure<T> {
    friend std::ostream& operator << (std::ostream& os, const Hexagon<T> &fig) {
        os << "Hexagon\n" << fig._points;
        return os;
    }
    friend std::istream& operator >> (std::istream& is, const Hexagon<T> &fig) {
        Array<Point<T>> tmpV;
        Point<T> tmp;
        for (size_t i = 0; i < Figures::Hexagon; ++i) {
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
        Hexagon();
        Hexagon(const std::initializer_list<Point<T>> &list);
        Hexagon(const Hexagon<Point<T>> &other);
        Hexagon(Hexagon<Point<T>> &&other) noexcept;
        Hexagon(const Array<Point<T>> &arr);
        virtual ~Hexagon() noexcept = default;

        Point<T> getCenter() const;
        operator double() const;

        bool operator==(const Figure<T> &other) const;
        Hexagon<T> &operator = (Figure<T> &other);
    private:
        bool valid(const Array<Point<T>> &tmp);
};

