#include "octagon.h"

const double octagonConst = 1 + pow(2, 0.5);

Octagon::Octagon() : Figure() {}

Octagon::Octagon(const std::vector<Point> & points) {
    if (points.size() != 8) {
        throw std::range_error("invalid number of coordinates");
    } else if (!valid(points)){
        throw std::range_error("Error! Square Constructor: invalid points");
    } else {
        _points = points;
    }
}

Octagon::Octagon(const Octagon &other) : Figure(other) {}

Octagon::Octagon(const Octagon &&other) : Figure(other) {}


bool Octagon::valid(const std::vector<Point> &p) const{
    for (size_t i = 0; i < 8 - 2; ++i) {
        if (fabs(p[i].distance(p[i+1]) - p[i+1].distance(p[i+2])) > EPSILON) return false;
    }
    double l = p[0].distance(p[1]);
    for (size_t i = 0; i < 8 - 4; ++i) {
        if (fabs(p[i].distance(p[i+4]) - 2 * l * sqrt(octagonConst / (octagonConst - 1))) > EPSILON) return false;
    }
    if (l < EPSILON) return false;
    return true;
}

Octagon::operator double() const {
    if ((*this).getPoints().size() == 0) {
        throw std::range_error("can't get square of empty");
    }
    return std::pow(this->_points[0].distance(this->_points[1]), 2) * 2 * octagonConst;
}

bool Octagon::isEqual(const Figure &other) const {
    if (_points.size() == 0 || other.getPoints().size() == 0) {
        throw std::range_error("can't compare empty figures");
    }
    return fabs(other.getPoints()[0].distance(other.getPoints()[1]) - _points[0].distance(_points[1])) < EPSILON;
}

Point Octagon::getCenter() const {
    if ((*this)._points.size() == 0) {
        throw std::range_error("can't get center of empty");
    }
    Point tmp = getAv(this->_points);
    return tmp;
}

void Octagon::print(std::ostream& os) const{
    if (_points.size() == 0) {
        throw std::logic_error("can't print empty figure");
    }
    for (size_t i = 0; i < 8; i++) {
        os << _points[i];
    }
}

void Octagon::input(std::istream &is) {
    std::vector<Point> tmpV;
    Point tmp;
    for (size_t i = 0; i < 8; ++i) {
        is >> tmp;
        tmpV.push_back(tmp);
    }
    if (!valid(tmpV)) {
        throw std::range_error("Error! Square Constructor: invalid points");
    } else {
        _points = tmpV;
    }
}

Octagon &Octagon::operator=(const Octagon &other) {
    _points = other._points;
    return *this;
}

Octagon &Octagon::operator=(const Octagon &&other) {
    _points = std::move(other._points);
    return *this;
}