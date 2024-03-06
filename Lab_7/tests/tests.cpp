#include <gtest/gtest.h>

#include "../header/FightManager.h"

std::map<HeroesClass, std::shared_ptr<Visitor>> v = {
    {DRAGON, std::make_shared<KnightVisitor>()},
    {KNIGHT, std::make_shared<DragonVisitor>()},
    {PEGASUS, std::make_shared<PegasusVisitor>()}
};

TEST(test_01, KnightConstructorTest)
{
    bool test = true;
    try {
        Knight(getRandNameKn(), 17, 17);
    } catch (std::range_error &ex) {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_02, PegasusConstructorTest)
{

    bool test = true;
    try{
        Pegasus(getRandNamePg(), 17, 17);
    } catch (std::range_error &ex) {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_03, DragonConstructorTest)
{

    bool test = true;
    try{
        Dragon(getRandNameDr(), 17, 17);
    } catch (std::range_error &ex) {
        std::cerr << " new throw exception:" << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
}

TEST(test_04, CloseTestKnight)
{

    Knight a(getRandNameKn(), 1, 1);

    std::shared_ptr<Heroes> f = std::shared_ptr<Heroes>(new Dragon(getRandNameKn(), 5, 0));
    
    ASSERT_TRUE(a.isClose(f));
}

TEST(test_05, CloseTestPegasus)
{

    Pegasus a(getRandNamePg(), 1, 1);

    std::shared_ptr<Heroes> f = std::shared_ptr<Heroes>(new Dragon(getRandNamePg(), 5, 0));
    
    ASSERT_TRUE(a.isClose(f));
}

TEST(test_06, CloseTestDragon)
{

    Dragon a(getRandNameDr(), 1, 1);

    std::shared_ptr<Heroes> f = std::shared_ptr<Heroes>(new Dragon(getRandNameKn(), 9, 0));
    
    ASSERT_TRUE(a.isClose(f));
}

TEST(test_07, CloseTestFalse)
{

    Knight a(getRandNameKn(), 1, 1);

    std::shared_ptr<Heroes> f = std::shared_ptr<Heroes>(new Dragon(getRandNameKn(), 7, 0));
    
    ASSERT_FALSE(a.isClose(f));
}

TEST(test_08, KnightFightTest)
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

TEST(test_09, PegasusFightTest)
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

TEST(test_10, DragonFightTest)
{
    set_t array;

    Factory factor;

    array.insert(factor.createHero(DRAGON, 0, 0));
    array.insert(factor.createHero(DRAGON, 0, 1));
    array.insert(factor.createHero(DRAGON, 0, 2));
    
    set_t dead = battle(array);
    ASSERT_TRUE(dead.size() == 0);
}

TEST(test_11, ZeroTest)
{
    set_t array;

    Factory factor;
    array.insert(factor.createHero(DRAGON, 10, 10));
    int countD = 0;
    for(int i = 0; i < 10; ++i) {
        for (std::shared_ptr<Heroes> npc : array) {
            for (std::shared_ptr<Heroes> other : array) {
                if (other != npc) {
                    if (npc->isAlive()) {
                        if(other->isAlive()) {
                            if (npc->isClose(other)) {
                                if (other->accept(v[npc->getType()], npc)) {
                                    other->mustDie();
                                    ++countD;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ASSERT_TRUE(countD == 0);
}

TEST(test_12, FabricTest)
{
    set_t arr;
    Factory fact;

    arr.insert(fact.createHero(KNIGHT, 1, 2));
    arr.insert(fact.createHero(PEGASUS, 3, 4));
    arr.insert(fact.createHero(DRAGON, 5, 6));

    bool res = (arr.size() == 3);

    EXPECT_TRUE(res);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
