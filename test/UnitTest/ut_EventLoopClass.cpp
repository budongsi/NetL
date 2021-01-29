#include "EventLoop.h"
#include <gtest/gtest.h>

TEST(EventLoopClass,DefautConstructor)
{
   EventLoop el;

   EXPECT_EQ(el.isLooping(),false);
}

int main(int argc, char** argv)
{
   testing::InitGoogleTest(&argc,argv);
   return RUN_ALL_TESTS();
}

