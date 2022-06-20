
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
//#include <QObject>
//#include "../ShortFormMaker/VideoEditorViewModel.h"
//#include "../ShortFormMaker/Editor.h"
#include "../ShortFormMaker/interface.h"
//#include "../ShortFormMaker/interface.cpp"
using namespace testing;

//QString m_inputInfo

TEST(iOpenTest, positiveTest1)
{
//    VideoEditorViewModel *videoEditorViewModel=new VideoEditorViewModel();
    std::string src= "C:\\user\\user\\desktop\\VideoSample\\VideoSample1";
    Interface *interface=new Interface();
//    Interface *interface;
//    EXPECT_EQ(videoEditorViewModel->open(src), SUCCESS);
    EXPECT_EQ(interface->iOpen(src),SUCCESS);
    ASSERT_THAT(0, Eq(0));
}

