#include <gtest/gtest.h>
#include "solve.h"

TEST(test_01, test) {
    string s = "321";
    string z = "963";
    Decimal a(s);
    Decimal b(z);
    a += b;
    ASSERT_EQ(a.getvalue(), "1284");
}

TEST(test_02, test) {
    string s = "321";
    Decimal a(s);
    Decimal b(s);
    a -= b;
    ASSERT_EQ(a.getvalue(), "0");
}

TEST(test_03, test) {
    string s = "321";
    Decimal a(s);
    Decimal b;
    b = a;
    ASSERT_EQ(b.getvalue(), s);
}

TEST(test_04, test) {
    string s = "321";
    Decimal a(s);
    Decimal b(s);
    a += b;
    ASSERT_EQ(a.getvalue(),"642");
}

TEST(test_05, test) {
    string s = "0";
    Decimal a(s);
    Decimal b(s);
    a += b;
    ASSERT_EQ(a.getvalue(),"0");
}

TEST(test_06, test) {
    string s = "0";
    Decimal a(s);
    Decimal b(s);
    a -= b;
    ASSERT_EQ(a.getvalue(),"0");
}

TEST(test_07, test) {
    string s = "123";
    string z = "1";
    Decimal a(s);
    Decimal b(z);
    a -= b;
    ASSERT_EQ(a.getvalue(),"122");
}

TEST(test_08, test) {
    string s = "123";
    Decimal a;
    Decimal b(s);
    ASSERT_ANY_THROW(a - b);
}

TEST(test_09, test) {
    string s = "123";
    Decimal a;
    Decimal b(s);
    ASSERT_ANY_THROW(a -= b);
}

TEST(test_10, test) {
    ASSERT_ANY_THROW(Decimal ("$"));
}

TEST(test_11, test) {
    string s = "124";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a > b);
}

TEST(test_12, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a == b);
}

TEST(test_13, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a <= b);
}

TEST(test_14, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a >= b);
}

TEST(test_15, test) {
    string s = "125";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a > b);
}

TEST(test_16, test) {
    string s = "125";
    Decimal a(s);
    Decimal b;
    ASSERT_TRUE(a > b);
}

TEST(test_17, test) {
    Decimal a("444"), b("44444");
    ASSERT_ANY_THROW(a -= b);
}

TEST(test_18, test) {
    Decimal a("444"), b("44444");
    ASSERT_ANY_THROW(a - b);
}

TEST(test_19, test) {
    ASSERT_ANY_THROW(Decimal("2A"));
}

TEST(test_20, test) {
    Decimal a("444");
    ASSERT_ANY_THROW(Decimal("0") - a);
}

TEST(test_21, test) {
    ASSERT_TRUE(Decimal("0") - Decimal("0") == Decimal("0"));
}

TEST(test_22, test) {
    ASSERT_TRUE(Decimal("0") + Decimal("0") == Decimal("0"));
}

TEST(test_23, test) {
    Decimal a("0");
    ASSERT_TRUE(Decimal("0") == a);
}

TEST(test_24, test) {
    string s = "12";
    Decimal a("134");
    ASSERT_TRUE(Decimal("146") - a == Decimal(s));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
