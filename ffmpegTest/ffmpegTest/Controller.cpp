#include <iostream>
#include <vector>

#include "videoInfo.h"
#include "saveInfo.h"
#include "concatFiles.h"
#include "splitFiles.h"

int main()
{
	std::vector<videoInfo> folder = std::vector<videoInfo>();
	folder = save("test");
	//concat(folder);
	split("test\\file_example_MP4_480_1_5MG.mp4");
}