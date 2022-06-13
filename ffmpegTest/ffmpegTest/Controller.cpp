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

	int start_time, end_time;
	split(15, 45, "test\\sample-mp4-file.mp4");
}