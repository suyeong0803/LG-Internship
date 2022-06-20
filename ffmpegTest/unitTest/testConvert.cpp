#include "pch.h"
#include "../ffmpegTest/Editor.h"

TEST(convertTest, positiveTest1)
{
	Editor* editor = new Editor();
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(editor->convert("D:\\test\\testVideo5\\" + std::to_string(i + 1) + ".tp", "D:\\convert\\output_convert" + std::to_string(i) + ".mp4"), SUCCESS);

	}
}