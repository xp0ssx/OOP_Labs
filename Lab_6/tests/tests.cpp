#include <gtest/gtest.h>

#include "../header/Battle.h"
#include "../header/FactoryHeroes.h"

TEST(test_01, KnightConstructorTest)
{

    bool test = true;
    try
    {
        Knight(getRandNameKn(), 17, 17);
    }
    catch (std::range_error &ex)
    {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_02, PegasusConstructorTest)
{

    bool test = true;
    try
    {
        Pegasus(getRandNamePg(), 17, 17);
    }
    catch (std::range_error &ex)
    {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_03, DragonConstructorTest)
{

    bool test = true;
    try
    {
        Dragon(getRandNameDr(), 17, 17);
    }
    catch (std::range_error &ex)
    {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_04, CloseTest)
{

    Knight a(getRandNameKn(), 1, 1);

    std::shared_ptr<Heroes> f = std::shared_ptr<Heroes>(new Knight(getRandNameKn(), 99, 0));

    ASSERT_TRUE(a.isClose(f));
}

TEST(test_05, NoDeathFighterTest)
{

    set_t array;

    Factory factor;

    array.insert(factor.createHero(KNIGHT, 0, 0));
    array.insert(factor.createHero(PEGASUS, 100, 100));
    array.insert(factor.createHero(DRAGON, 200, 200));

    set_t dead = battle(array);

    bool result = (dead.size() == 0);

    EXPECT_TRUE(result);
}

TEST(test_06, DeathFighterTest)
{
    set_t array;

    Factory factor;

    array.insert(factor.createHero(KNIGHT, 0, 0));
    array.insert(factor.createHero(PEGASUS, 0, 100));
    array.insert(factor.createHero(DRAGON, 1, 99));

    set_t dead = battle(array);

    bool result = (dead.size() == 2);

    EXPECT_TRUE(result);
}

TEST(test_07, KnightFightTest)
{
    set_t array;

    Factory factor;

    array.insert(factor.createHero(KNIGHT, 0, 0));
    array.insert(factor.createHero(KNIGHT, 0, 1));
    array.insert(factor.createHero(KNIGHT, 0, 2));

    set_t dead = battle(array);

    bool result = (dead.size() == 0);

    EXPECT_TRUE(result);
}

TEST(test_08, PegasusFightTest)
{
    set_t array;

    Factory factor;

    array.insert(factor.createHero(PEGASUS, 0, 0));
    array.insert(factor.createHero(PEGASUS, 0, 1));
    array.insert(factor.createHero(PEGASUS, 0, 2));

    set_t dead = battle(array);

    bool result = (dead.size() == 0);

    EXPECT_TRUE(result);
}

TEST(test_09, DragonFightTest)
{
    set_t array;

    Factory factor;

    array.insert(factor.createHero(DRAGON, 0, 0));
    array.insert(factor.createHero(DRAGON, 0, 1));
    array.insert(factor.createHero(DRAGON, 0, 2));

    set_t dead = battle(array);

    bool result = (dead.size() == 0);

    EXPECT_TRUE(result);
}

TEST(test_10, KnightWithPegasusFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(KNIGHT, 10, 10));
    array.insert(factor.createHero(PEGASUS, 0, 0));
    array.insert(factor.createHero(PEGASUS, 100, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 2);

    EXPECT_FALSE(result);
}

TEST(test_11, KnightWithDragonFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(KNIGHT, 10, 10));
    array.insert(factor.createHero(DRAGON, 0, 0));
    array.insert(factor.createHero(DRAGON, 100, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 2);

    EXPECT_TRUE(result);
}

TEST(test_12, PegasusWithKnightFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(PEGASUS, 10, 10));
    array.insert(factor.createHero(KNIGHT, 0, 0));
    array.insert(factor.createHero(KNIGHT, 100, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 1);

    EXPECT_FALSE(result);
}

TEST(test_13, KnightWithDragonFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(PEGASUS, 10, 10));
    array.insert(factor.createHero(DRAGON, 0, 0));
    array.insert(factor.createHero(DRAGON, 100, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 2);

    EXPECT_FALSE(result);
}

TEST(test_14, DragonWithKnightFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(DRAGON, 10, 10));
    array.insert(factor.createHero(KNIGHT, 0, 0));
    array.insert(factor.createHero(KNIGHT, 100, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 1);

    EXPECT_TRUE(result);
}

TEST(test_15, DragonWithPegasusFightTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(DRAGON, 10, 10));
    array.insert(factor.createHero(PEGASUS, 0, 0));
    array.insert(factor.createHero(PEGASUS, 10, 0));

    set_t dead = battle(array);

    bool result = (dead.size() == 2);

    EXPECT_TRUE(result);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
