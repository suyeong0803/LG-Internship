#include "pch.h"
#include "../ffmpegTest/Editor.h"

TEST(concatTest, positiveTest1)
{
	Editor* editor = new Editor();
	editor->saveInfo("D:\\test\\testVideo5");
	
	EXPECT_EQ(editor->concat(0, 42746201), SUCCESS);
}