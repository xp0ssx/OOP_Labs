#include "figure.h"

Figure::Figure() {
    std::vector<Point> points;
    _points = points;
}

Figure::Figure(const Figure &other) : _points(other._points) {}

Figure::Figure(const Figure &&other) noexcept{
    _points = std::move(other._points);
}

std::ostream& operator << (std::ostream& os, const Figure& p) {
    p.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Figure& f) {
    f.input(is);
    return is;
}

std::vector<Point> Figure::getPoints() const{
    return _points;
}

bool operator == (const Figure& lhs, const Figure& rhs) {
    if (typeid(lhs) != typeid(rhs)) {
        return false;
    }
    return lhs.isEqual(rhs);
}



