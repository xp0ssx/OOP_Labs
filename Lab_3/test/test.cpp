#include "triangle.h"
#include "octagon.h"
#include "hexagon.h"
#include "array.h"
#include "generator.h"
#include <gtest/gtest.h>

TEST(PointConstructorDefault, test_00) {
    Point p1;
    ASSERT_TRUE(p1.getX() == 0 && p1.getY() == 0);
}

TEST(PointConstructorByCoordinates, test_00) {
    Point p1(1, 2);
    ASSERT_TRUE(fabs(p1.getX() - 1) < EPSILON && fabs(p1.getY() - 2)< EPSILON);
}

TEST(PointConstructorByCoordinates, test_01) {
    Point p1(-10.3, 12.4);
    ASSERT_TRUE(fabs(p1.getX() - (-10.3)) < EPSILON && fabs(p1.getY() - 12.4) < EPSILON);
}

TEST(PointConstructorByCoordinates, test_02) {
    Point p1(17.1123, -56.489);
    ASSERT_TRUE(fabs(p1.getX() - 17.1123) < EPSILON && fabs(p1.getY() - (-56.489)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_00) {
    Point p1(Point(3,4));
    ASSERT_TRUE(fabs(p1.getX() - 3) < EPSILON && fabs(p1.getY() - 4) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_01) {
    Point p1(Point(-10,-0.123112));
    ASSERT_TRUE(fabs(p1.getX() - (-10)) < EPSILON && fabs(p1.getY() - (-0.123112)) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_02) {
    Point p1(Point(0,0));
    ASSERT_TRUE(fabs(p1.getX()) < EPSILON && fabs(p1.getY()) < EPSILON);
}

TEST(PointConstructorByOtherPoint, test_03) {
    Point p1(Point(Point(4.1231, 313.109283)));
    ASSERT_TRUE(fabs(p1.getX() - 4.1231) < EPSILON && fabs(p1.getY() - 313.109283) < EPSILON);
}

TEST(PointEqualOperatorCheck_test_03_Test, test_00) {
    ASSERT_TRUE(Point(3,4) == Point(3,4));
}

TEST(PointEqualOperator, test_01) {
    ASSERT_TRUE(Point(3,5) != Point(3,4));
}

TEST(PointEqualOperator, test_02) {
    ASSERT_TRUE(Point(1.012, 0) != Point(1.1, 0));
}

TEST(PointEqualOperator, test_03) {
    ASSERT_TRUE(Point(-4, 1.03) != Point(9.123, 12434));
}

TEST(PointDistance, test_00) {
    Point p1(-9,2), p2(-10,-100);
    ASSERT_TRUE(fabs(p1.distance(p2) - 102.00) < EPSILON);
}

TEST(PointDistance, test_01) {
    Point p1(4,5), p2(8,0);
    ASSERT_TRUE(fabs(p1.distance(p2) - 6.40) < EPSILON);
}

TEST(PointDistance, test_02) {
    Point p1(12.3,-10.55), p2(-1.89,0.78);
    ASSERT_FALSE(fabs(p1.distance(p2) - 23.00) < EPSILON);
}

TEST(OperatorCopy, test_00) {
    Point p1(12.3,-10.55), p2;
    p2 = p1;
    ASSERT_TRUE(p2 == p1);
}

TEST(TriangleVectorConstructor, test00) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(TriangleVectorConstructor, test01) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(TriangleVectorConstructor, test02) {
    ASSERT_THROW(Triangle t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(TriangleVectorConstructor, test03) {
    ASSERT_NO_THROW(Triangle t(GenerateFigures(3)));
}

TEST(TriangleCopyConstructor, test00) {
    Triangle t(GenerateFigures(3));
    Triangle t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleMoveConstructor, test00) {
    Triangle t(GenerateFigures(3));
    Triangle t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(TriangleSquare, test00) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(fabs(double(t) - 3.2111) < EPSILON);
}

TEST(TriangleSquare, test01) {
    Triangle t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(TriangleAverage, test00) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t.getCenter() == Point(1.83, 2.28));
}

TEST(TriangleAverage, test01) {
    Triangle t(std::vector<Point>{Point(-7.55,-3.16), Point(-5.63,-4.58), Point(-5.36, -2.21)});
    ASSERT_TRUE(t.getCenter() == Point(-6.18,-3.31));
}

TEST(TriangleAverage, test02) {
    Triangle t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(TriangleOperatorMove, test00) {
    Triangle t(GenerateFigures(3)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(TriangleOperatorCopy, test00) {
    Triangle t(GenerateFigures(3)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(HexagonVectorConstructor, test00) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(HexagonVectorConstructor, test01) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(HexagonVectorConstructor, test02) {
    ASSERT_THROW(Hexagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(HexagonVectorConstructor, test03) {
    ASSERT_NO_THROW(Hexagon t(GenerateFigures(6)));
}

TEST(HexagonCopyConstructor, test00) {
    Hexagon t(GenerateFigures(6));
    Hexagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonMoveConstructor, test00) {
    Hexagon t(GenerateFigures(6));
    Hexagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(HexagonSquare, test00) {
    Hexagon t(std::vector<Point> {Point(-2,9), Point(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(fabs(double(t) - 1252.27) < EPSILON);
}

TEST(HexagonSquare, test01) {
    Hexagon t;
    ASSERT_THROW((double) t, std::range_error);
}

TEST(HexagonAverage, test00) {
    Hexagon t(std::vector<Point> {Point(-2,9), Point(9,-10), Point(30.95,-9.97), Point(41.91, 9.05), Point(30.91, 28.05), Point(8.95,28.03)});
    ASSERT_TRUE(t.getCenter() == Point(19.95, 9.03));
}

TEST(HexagonAverage, test01) {
    Hexagon t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(HexagonOperatorMove, test00) {
    Hexagon t(GenerateFigures(6)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(HexagonOperatorCopy, test00) {
    Hexagon t(GenerateFigures(6)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(OctagonVectorConstructor, test00) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6)}), std::range_error);
}

TEST(OctagonVectorConstructor, test01) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4)}), std::range_error);
}

TEST(OctagonVectorConstructor, test02) {
    ASSERT_THROW(Octagon t(std::vector<Point> {Point(1,2), Point(3,4), Point(5,6), Point(6,7)}), std::range_error);
}

TEST(OctagonVectorConstructor, test03) {
    ASSERT_NO_THROW(Octagon t(GenerateFigures(8)));
}

TEST(OctagonCopyConstructor, test00) {
    Octagon t(GenerateFigures(8));
    Octagon t1(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonMoveConstructor, test00) {
    Octagon t(GenerateFigures(8));
    Octagon t1(std::move(t));
    ASSERT_TRUE(t == t1);
}

TEST(OctagonSquare, test00) {
    Octagon t(std::vector<Point> {Point(-5,0), Point(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(double(t) - 1023.63 < EPSILON);
}

TEST(OctagonSquare, test01) {
    Octagon t1;
    ASSERT_THROW((double) t1, std::range_error);
}

TEST(OctagonAverage, test00) {
    Octagon t(std::vector<Point> {Point(-5,0), Point(9,-4), Point(21.73, 3.07), Point(25.73, 17.07), Point(18.66, 29.80), Point(4.66, 33.80), Point(-8.07, 26.73), Point(-12.07, 12.73)});
    ASSERT_TRUE(t.getCenter() == Point(6.83, 14.9));
}

TEST(OctagonAverage, test01) {
    Octagon t;
    ASSERT_THROW(t.getCenter(), std::range_error);
}

TEST(OctagonOperatorMove, test00) {
    Octagon t(GenerateFigures(8)), t1;
    t1 = std::move(t);
    ASSERT_TRUE(t == t1);
}

TEST(OctagonOperatorCopy, test00) {
    Octagon t(GenerateFigures(8)), t1;
    t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(ArrayInitListConstructor, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar({&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar.getArr()[0] != o1) f = false;
    if (*ar.getArr()[1] != o2) f = false;
    if (*ar.getArr()[2] != h1) f = false;
    if (*ar.getArr()[3] != t1) f = false;
    ASSERT_TRUE(f);
}

TEST(ArrayVectorConstructor, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    bool f = true;
    if (*ar.getArr()[0] != o1) f = false;
    if (*ar.getArr()[1] != o2) f = false;
    if (*ar.getArr()[2] != h1) f = false;
    if (*ar.getArr()[3] != t1) f = false;
    ASSERT_TRUE(f);
}

TEST(ArraySumSquare, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ASSERT_TRUE(fabs(double(ar) - (double(o1) + double(o2) + double(h1) + double(t1))) < EPSILON);
}

TEST(ArraySumSquare, test01) {
    FigureArray ar;
    ASSERT_THROW((double) ar, std::range_error);
}

TEST(ArrayPushBack, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ar.push_back(&h2);
    ASSERT_TRUE(*ar.getArr()[ar.getSize() - 1] == h2);
}

TEST(ArrayPopBack, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ar.pop_back();
    ASSERT_TRUE(ar.getSize() == 3 && *ar.getArr()[ar.getSize() - 1] == h1);
}

TEST(ArrayPopBack, test01) {
    FigureArray ar;
    ASSERT_THROW(ar.pop_back(), std::range_error);
}

TEST(ArrayErase, test00) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    bool f = true;
    ar.erase(2);
    if (*ar.getArr()[0] != o1) f = false;
    if (*ar.getArr()[1] != o2) f = false;
    if (*ar.getArr()[2] != t1) f = false;
    ASSERT_TRUE(ar.getSize() == 3 && f);
}

TEST(ArrayErase, test01) {
    FigureArray ar;
    ASSERT_THROW(ar.erase(1), std::range_error);
}

TEST(ArrayErase, test02) {
    Octagon o1(GenerateFigures(8)), o2(GenerateFigures(8));
    Hexagon h1(GenerateFigures(6)), h2(GenerateFigures(6));
    Triangle t1(GenerateFigures(3));
    FigureArray ar(std::vector<Figure *> {&o1, &o2, &h1, &t1});
    ASSERT_THROW(ar.erase(10), std::range_error);
}

TEST(FiguresEqualTest, test00) {
    Triangle t(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    Triangle t1(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test01) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Triangle t1(std::vector<Point>{Point(0.79, 1.1), Point(3.37, 1.98), Point(1.32, 3.77)});
    ASSERT_TRUE(t == t1);
}

TEST(FiguresEqualTest, test02) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Hexagon h(GenerateFigures(6));
    ASSERT_FALSE(t == h);
}

TEST(FiguresEqualTest, test03) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Octagon o(GenerateFigures(8));
    ASSERT_FALSE(t == o);
}

TEST(FiguresEqualTest, test04) {
    Triangle t(std::vector<Point>{Point(3.37, 1.98), Point(0.79, 1.1), Point(1.32, 3.77)});
    Triangle t1(std::vector<Point>{Point(-7.55,-3.16), Point(-5.63,-4.58), Point(-5.36, -2.21)});
    ASSERT_FALSE(t == t1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
