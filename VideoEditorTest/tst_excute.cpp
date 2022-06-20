
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../ShortFormMaker/interface.h"
using namespace testing;

TEST(excuteTestSet, excuteTest)
{
    Interface *interface=new Interface();
    std::string src= "C:\\user\\user\\desktop\\VideoSample\\VideoSample1\\output.mp4";
    EXPECT_EQ(interface->iExcute(0,39999,src),SUCCESS );
//    ASSERT_THAT(0, Eq(0));
}

