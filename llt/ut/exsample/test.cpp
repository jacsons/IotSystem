#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int Foo(int a,int b)
{
 return a+b;
}

TEST(FooTest, ZeroEqual)
{
 ASSERT_EQ(0,0);
}

TEST(FooTest, HandleNoneZeroInput)
{
    EXPECT_EQ(12,Foo(4, 10));
    EXPECT_EQ(6, Foo(30, 18));
}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
