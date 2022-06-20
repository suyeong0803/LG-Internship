#include "pch.h"
#include "../ffmpegTest/Editor.h"

TEST(saveTest, positiveTest1)
{
	Editor *editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\testVideo5"), SUCCESS);
}

TEST(saveTest, positiveTest2)
{
	Editor* editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\testVideo50"), SUCCESS);
}
TEST(saveTest, negativeTest1)
{
	Editor* editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\testVideo51"), ERR_MAXFILES);
}
TEST(saveTest, negativeTest2)
{
	Editor* editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\none"), ERR_NOTEXIST);
}
TEST(saveTest, negativeTest3)
{
	Editor* editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\testText"), ERR_INPUTOPEN);
}
TEST(saveTest, negativeTest4)
{
	Editor* editor = new Editor();
	EXPECT_EQ(editor->saveInfo("D:\\test\\testEmpty"), ERR_EMPTYFOLDER);
}