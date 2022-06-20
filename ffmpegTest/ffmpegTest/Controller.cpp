<<<<<<< HEAD
#include "Editor.h"

int main()
{
	Editor *videoEditor = new Editor();
	std::string folderPath = videoEditor->getInputPath(); // -> user

	int result = 100;

	result = videoEditor->saveInfo(folderPath);
	if (result != SUCCESS)
	{
		if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
		if (result == ERR_NOTEXIST) return ERR_NOTEXIST;
		if (result == ERR_EMPTYFOLDER) return ERR_EMPTYFOLDER;

		return ERR_SAVEINFO;
	}

	//std::filesystem::create_directory("D:\\convert");
	//for (int i = 0; i < videoEditor->getInfoSize(); i++)
	//{
	//  result = videoEditor->convert(videoEditor->getInfo(i).m_path, "D:\\convert\\output_convert" + std::to_string(i) + ".mp4");
	//	if (result != SUCCESS)
	//	{
	//		if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
	//		return ERR_CONVERT;
	//	}
	//}

	int64_t startTime = 650000, endTime = 3200000; // -> user
	//int64_t startTime = videoEditor->getStartTime(), endTime = videoEditor->getEndTime(); // -> user
	result = videoEditor->concat(startTime, endTime);
	if (result < SUCCESS)
		return ERR_CONCAT;

	else videoEditor->setIndex(result);

	std::string final_output = "D:\\output.mp4";
	//std::string final_output = videoEditor->getOutputPath();
	result = videoEditor->split(videoEditor->getIndex(), startTime, endTime, final_output);
	if (result != SUCCESS)
	{
		if (result == ERR_OUTPUTCREATE) return ERR_OUTPUTCREATE;
		return ERR_SPLIT;
	}

	Sleep(1);
	videoEditor->remove();
=======
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
>>>>>>> 11cd1f6bdb032eccbfb743d8e3f9b1a0d05968a5
}