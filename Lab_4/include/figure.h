#pragma once
#include "point.h"

namespace Figures {
    const size_t Triangle = 3;
    const size_t Hexagon = 6;
    const size_t Octagon = 8;
}
template <typename T>
class Figure {
    friend std::ostream& operator << (std::ostream& os, const Figure<T> &fig) {
        switch (fig._points.size()) {
        case Figures::Triangle:
            os << "Triangle\n" << fig._points;
            break;
        case Figures::Hexagon:
            os << "Hexagon\n" << fig._points;
            break;
        case Figures::Octagon:
            os << "Octagon\n" << fig._points;
            break;
        default:
            os << "Unknown figure\n" << fig._points;
            break;
        }
        return os;
    }
    public:
        Figure();
        Figure(const Figure<Point<T>> &other);
        Figure(Figure<Point<T>> &&other) noexcept;
        Figure(const std::initializer_list<Point<T>> &list);
        ~Figure() = default;
        Array<Point<T>> getPoints() const;

        virtual operator double() const = 0;
        virtual Point<T> getCenter() const = 0;
    protected:
        Array<Point<T>> _points;
};
