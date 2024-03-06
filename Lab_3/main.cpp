#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "time.h"
#include "array.h"
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

int main() {
    srand(time(NULL));
    Hexagon h1;
    Octagon o1;
    Triangle t1;
    std::cout << "Print figures for array.\n";
    FigureArray ar({&h1,&o1,&t1});
    for (size_t i = 0; i < ar.getSize(); ++i) {
        std::cin >> *ar.getArr()[i];
    }
    for (size_t i = 0; i < ar.getSize(); ++i) {
        std::cout << *ar.getArr()[i];
    }
    for (size_t i = 0; i < ar.getSize(); ++i) {
        std::cout << (*ar.getArr()[i]).getCenter() << ' ' << double (*ar.getArr()[i]) << std::endl;
    }
}