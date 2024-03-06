#include "point.h"

template <typename T>
Array<Point<T>> GenerateFigures(int n) {
    Array<Point<T>> res;
    Point<T> p1(rand() % 10 - 10, rand() % 20 - 10), p2(rand() % 20 - 10 , rand() % 20 - 10);
    res.push_back(p1);
    res.push_back(p2);
    for (size_t i = 0; i < n - 2; ++i) {
        T x = (res[i].getX()-res[i+1].getX())*cos(-(n-2) * PI / n)-(res[i].getY()-res[i+1].getY())*sin(-(n-2) * PI / n)+res[i+1].getX();
        T y = (res[i].getX()-res[i+1].getX())*sin(-(n-2) * PI / n)+(res[i].getY()-res[i+1].getY())*cos(-(n-2) * PI / n)+res[i+1].getY();
        res.push_back(Point<T>(x,y));
    }
    return res;
}