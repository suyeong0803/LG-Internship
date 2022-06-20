#include "pch.h"
#include "../ffmpegTest/Editor.h"

TEST(splitTest, positiveTest1)
{
	Editor* editor = new Editor();
	editor->saveInfo("D:\\test\\testVideo5");

	EXPECT_EQ(editor->split(0, 650000, 3200000, "D:\\output.mp4"), SUCCESS);
}

TEST(splitTest, negativeTest1)
{
	Editor* editor = new Editor();
	editor->saveInfo("D:\\test\\testVideo5");

	EXPECT_EQ(editor->split(0, 650000, 3200000, "D:\\none\\output.mp4"), ERR_OUTPUTOPEN);
}