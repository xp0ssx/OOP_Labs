#include "octagonSRC.h"
#include "triangleSRC.h"
#include "hexagonSRC.h"
#include "figure-array.h"
#include "arraySRC.h"
#include "pointSRC.h"
#include "figureSRC.h"
#include "generatorSRC.h"
#include <gtest/gtest.h>


TEST(PointConstructorByCoordinates, test_00) {
    Point<int> p1(1, 2);
    ASSERT_TRUE(fabs(p1.getX() - 1) < EPSILON && fabs(p1.getY() - 2)< EPSILON);
}

TEST(PointConstructorByCoordinates, test_01) {
    Point<double> p1(-10.3, 12.4);
    ASSERT_TRUE(fabs(p1.getX() - (-10.3)) < EPSILON && fabs(p1.getY() - 12.4) < EPSILON);
}

TEST(PointConstructorByCoordinates, test_02) {
    Point<double> p1(17.1123, -56.489);
    ASSERT_TRUE(fabs(p1.getX() - 17.1123) < EPSILON && fabs(p1.getY() - (-56.489)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_00) {
    Point<int> p1(Point<int>(3,4));
    ASSERT_TRUE(fabs(p1.getX() - 3) < EPSILON && fabs(p1.getY() - 4) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_01) {
    Point<double> p1(Point<double>(-10,-0.123112));
    ASSERT_TRUE(fabs(p1.getX() - (-10)) < EPSILON && fabs(p1.getY() - (-0.123112)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_02) {
    Point<int> p1(Point<int>(0,0));
    ASSERT_TRUE(fabs(p1.getX()) < EPSILON && fabs(p1.getY()) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_03) {
    Point<double> p1(Point<double>(Point<double>(4.1231, 313.109283)));
    ASSERT_TRUE(fabs(p1.getX() - 4.1231) < EPSILON && fabs(p1.getY() - 313.109283) < EPSILON);
}

TEST(PointEqualOperatorCheck_test_03_Test, test_00) {
    ASSERT_TRUE(Point(3,4) == Point(3,4));
}

TEST(PointEqualOperator, test_01) {
    ASSERT_TRUE(Point(3,5) != Point(3,4));
}

TEST(PointEqualOperator, test_02) {
    ASSERT_TRUE(Point<double>(1.012, 0) != Point<double>(1.1, 0));
}

TEST(PointEqualOperator, test_03) {
    ASSERT_TRUE(Point<double>(-4, 1.03) != Point<double>(9.123, 12434));
}

TEST(PointDistance, test_00) {
    Point<int> p1(-9,2), p2(-10,-100);
    ASSERT_TRUE(fabs(p1.distance(p2) - 102.00) < EPSILON);
}

TEST(PointDistance, test_01) {
    Point<int> p1(4,5), p2(8,0);
    ASSERT_TRUE(fabs(p1.distance(p2) - 6.40) < EPSILON);
}

TEST(PointDistance, test_02) {
    Point<double> p1(12.3,-10.55), p2(-1.89,0.78);
    ASSERT_FALSE(fabs(p1.distance(p2) - 23.00) < EPSILON);
}

TEST(OperatorCopy, test_00) {
    Point<double> p1(12.3,-10.55), p2;
    p2 = p1;
    ASSERT_TRUE(p2 == p1);
}

TEST(TriangleVectorConstructor, test00) {
    ASSERT_THROW(Triangle<int> t(std::initializer_list<Point<int>> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(TriangleVectorConstructor, test01) {
    ASSERT_THROW(Triangle t(std::initializer_list<Point<int>>{Point(1,2), Point(3,4)}), std::range_error);
}

TEST(TriangleVectorConstructor, test02) {
    ASSERT_THROW(Triangle t(std::initializer_list<Point<int>> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(TriangleVectorConstructor, test03) {
    ASSERT_NO_THROW(Triangle<double> t(GenerateFigures<double>(3)));
}

TEST(TriangleCopyConstructor, test00) {
    Triangle<double> t(GenerateFigures<double>(3));
    Triangle<double> t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleMoveConstructor, test00) {
    Triangle<double> t(GenerateFigures<double>(3));
    Triangle<double> t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(TriangleSquare, test00) {
    Triangle<double> t(Array<Point<double>>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(fabs(double(t) - 3.2111) < EPSILON);
}

TEST(TriangleSquare, test01) {
    Triangle<double> t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(TriangleAverage, test00) {
    Triangle<double> t(Array<Point<double>>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t.getCenter() == Point(1.83, 2.28));
}

TEST(TriangleAverage, test01) {
    Triangle<double> t(Array<Point<double>>{Point(-7.55,-3.16), Point(-5.63,-4.58), Point(-5.36, -2.21)});
    ASSERT_TRUE(t.getCenter() == Point<double>(-6.18,-3.31));
}

TEST(TriangleAverage, test02) {
    Triangle<double> t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(TriangleOperatorMove, test00) {
    Triangle<double> t(GenerateFigures<double>(3)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleOperatorCopy, test00) {
    Triangle<double> t(GenerateFigures<double>(3)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(HexagonVectorConstructor, test00) {
    ASSERT_THROW(Hexagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(HexagonVectorConstructor, test01) {
    ASSERT_THROW(Hexagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(HexagonVectorConstructor, test02) {
    ASSERT_THROW(Hexagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(HexagonVectorConstructor, test03) {
    ASSERT_NO_THROW(Hexagon<double> t(GenerateFigures<double>(6)));
}

TEST(HexagonCopyConstructor, test00) {
    Hexagon<double> t(GenerateFigures<double>(6));
    Hexagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonMoveConstructor, test00) {
    Hexagon<double> t(GenerateFigures<double>(6));
    Hexagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(HexagonSquare, test00) {
    Hexagon<double> t(Array<Point<double>> {Point<double>(-2,9), Point<double>(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(fabs(double(t) - 1252.27) < EPSILON);
}

TEST(HexagonSquare, test01) {
    Hexagon<double> t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(HexagonAverage, test00) {
    Hexagon<double> t(Array<Point<double>> {Point<double>(-2,9), Point<double>(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(t.getCenter() == Point(19.95, 9.03));
}

TEST(HexagonAverage, test01) {
    Hexagon<char> t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(HexagonOperatorMove, test00) {
    Hexagon<double> t(GenerateFigures<double>(6)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonOperatorCopy, test00) {
    Hexagon<double> t(GenerateFigures<double>(6)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(OctagonVectorConstructor, test00) {
    ASSERT_THROW(Octagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(OctagonVectorConstructor, test01) {
    ASSERT_THROW(Octagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(OctagonVectorConstructor, test02) {
    ASSERT_THROW(Octagon<int> t(Array<Point<int>> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(OctagonVectorConstructor, test03) {
    ASSERT_NO_THROW(Octagon<double> t(GenerateFigures<double>(8)));
}

TEST(OctagonCopyConstructor, test00) {
    Octagon<double> t(GenerateFigures<double>(8));
    Octagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonMoveConstructor, test00) {
    Octagon<double> t(GenerateFigures<double>(8));
    Octagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(OctagonSquare, test00) {
    Octagon<double> t(Array<Point<double>> {Point<double>(-5,0), Point<double>(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(double(t) - 1023.63 < EPSILON);
}

TEST(OctagonSquare, test01) {
    Octagon<double> t1;
    ASSERT_THROW((double) t1, std::range_error);
}

TEST(OctagonAverage, test00) {
    Octagon<double> t(Array<Point<double>> {Point<double>(-5,0), Point<double>(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(t.getCenter() == Point(6.83, 14.9));
}

TEST(OctagonAverage, test01) {
    Octagon<char> t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(OctagonOperatorMove, test00) {
    Octagon<double> t(GenerateFigures<double>(8)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonOperatorCopy, test00) {
    Octagon<double> t(GenerateFigures<double>(8)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(ArrayInitListConstructor, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon<double> h1(GenerateFigures<double>(6));
    Triangle<double> t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar({&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar[0] != o1) f = false;
    if (*ar[1] != o2) f = false;
    if (*ar[2] != h1) f = false;
    if (*ar[3] != t1) f = false;
    ASSERT_TRUE(f);
}

TEST(ArrayVectorConstructor, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon<double> h1(GenerateFigures<double>(6));
    Triangle<double> t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar[0] != o1) f = false;
    if (*ar[1] != o2) f = false;
    if (*ar[2] != h1) f = false;
    if (*ar[3] != t1) f = false;
    ASSERT_TRUE(f);
}

TEST(ArraySumSquare, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon<double> h1(GenerateFigures<double>(6));
    Triangle<double> t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    ASSERT_TRUE(fabs(getAreas(ar) - (double(o1) + double(o2) + double(h1) + double(t1))) < EPSILON);
}

TEST(ArraySumSquare, test01) {
    Array<Figure<double> *> ar;
    ASSERT_TRUE(fabs(getAreas(ar) - 0) == 0);
}

TEST(ArrayPushBack, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon<double> h1(GenerateFigures<double>(6)), h2(GenerateFigures<double>(6));
    Triangle<double> t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    ar.push_back(&h2);
    ASSERT_TRUE(*ar[ar.size() - 1] == h2);
}

TEST(ArrayPopBack, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon<double> h1(GenerateFigures<double>(6)), h2(GenerateFigures<double>(6));
    Triangle<double> t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    ar.pop_back();
    ASSERT_TRUE(ar.size() == 3 && *ar[ar.size() - 1] == h1);
}

TEST(ArrayPopBack, test01) {
    Array<Figure<double> *> ar;
    ASSERT_THROW(ar.pop_back(), std::range_error);
}

TEST(ArrayErase, test00) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon h1(GenerateFigures<double>(6)), h2(GenerateFigures<double>(6));
    Triangle t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    bool f = true;
    ar.erase(2);
    if (*ar[0] != o1) f = false;
    if (*ar[1] != o2) f = false;
    if (*ar[2] != t1) f = false;
    ASSERT_TRUE(ar.size() == 3 && f);
}

TEST(ArrayErase, test01) {
    Array<Figure<double> *> ar;
    ASSERT_THROW(ar.erase(1), std::range_error);
}

TEST(ArrayErase, test02) {
    Octagon<double> o1(GenerateFigures<double>(8)), o2(GenerateFigures<double>(8));
    Hexagon h1(GenerateFigures<double>(6)), h2(GenerateFigures<double>(6));
    Triangle t1(GenerateFigures<double>(3));
    Array<Figure<double> *> ar (Array<Figure<double> *> {&o1, &o2, &h1, &t1});
    ASSERT_THROW(ar.erase(10), std::range_error);
}

TEST(FiguresEqualTest, test00) {
    Triangle<double> t(Array<Point<double>>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    Triangle<double> t1(Array<Point<double>>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test01) {
    Triangle t(Array<Point<double>>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Triangle t1(Array<Point<double>>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test02) {
    Triangle t(Array<Point<double>>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Hexagon h(GenerateFigures<double>(6));
    ASSERT_FALSE(t == h);
}

TEST(FiguresEqualTest, test03) {
    Triangle t(Array<Point<double>>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Octagon<double> o(GenerateFigures<double>(8));
    ASSERT_FALSE(t == o);
}

TEST(FiguresEqualTest, test04) {
    Triangle t(Array<Point<double>>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Triangle t1(Array<Point<double>>{Point(-7.55,-3.16), Point(-5.63,-4.58), Point(-5.36, -2.21)});
    ASSERT_FALSE(t == t1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}