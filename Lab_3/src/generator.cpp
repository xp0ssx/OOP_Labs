#include "generator.h"

std::vector<Point> GenerateFigures(int n) {
    std::vector<Point> res;
    Point p1(rand() % 10 - 10, rand() % 20 - 10), p2(rand() % 20 - 10 , rand() % 20 - 10);
    res.push_back(p1);
    res.push_back(p2);
    for (size_t i = 0; i < n - 2; ++i) {
        double x = (res[i].getX()-res[i+1].getX())*cos(-(n-2) * PI / n)-(res[i].getY()-res[i+1].getY())*sin(-(n-2) * PI / n)+res[i+1].getX();
        double y = (res[i].getX()-res[i+1].getX())*sin(-(n-2) * PI / n)+(res[i].getY()-res[i+1].getY())*cos(-(n-2) * PI / n)+res[i+1].getY();
        res.push_back(Point(x,y));
    }
    return res;
}