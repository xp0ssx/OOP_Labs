#include <iostream>
#include <gtest/gtest.h>
#include "func.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(func(2, 7)== 6);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(func(2, 9)== 8);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(func(3, 10)== 9);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(func(4, 17)== 16);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(func(1, 7)== 7);
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(func(5, 26)== 25);
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(func(7, 22)== 21);
}

TEST(test_08, basic_test_set)
{
    ASSERT_TRUE(func(10, 35)== 30);
}

TEST(test_09, basic_test_set)
{
    ASSERT_TRUE(func(15, 17)== 15);
}

TEST(test_10, basic_test_set)
{
    ASSERT_TRUE(func(4, 13)== 12);
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
