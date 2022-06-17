#include "Editor.h"

int main()
{
	Editor *videoEditor = new Editor();
	std::string folderPath = "D:\\00000003REC"; // -> user

	int result = 100;

	if ((result = videoEditor->saveInfo(folderPath)) != SUCCESS)
	{
		if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
		if (result == ERR_NOTEXIST) return ERR_NOTEXIST;
		if (result == ERR_EMPTYFOLDER) return ERR_EMPTYFOLDER;

		return ERR_SAVEINFO;
	}

	std::filesystem::create_directory("D:\\convert");
	for (int i = 0; i < videoEditor->m_folder.size(); i++)
	{
		if (result = videoEditor->convert(videoEditor->m_folder[i].m_path, "D:\\convert\\output_convert" + std::to_string(i) + ".mp4") != SUCCESS)
		{
			if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
			return ERR_CONVERT;
		}
	}

	int64_t startTime = 16508987, endTime = 22342833; // -> user
	//int64_t startTime = videoEditor->getStartTime(), endTime = videoEditor->getEndTime(); // -> user
	if (result = videoEditor->concat(startTime, endTime) < SUCCESS)
		return ERR_CONCAT;
	else videoEditor->setIndex(result);


	std::string final_output = "D:\\output.mp4";
	//std::string final_output = videoEditor->getOutputPath();
	if (result = videoEditor->split(videoEditor->getIndex(), startTime, endTime, final_output) != SUCCESS)
	{
		if (result == ERR_OUTPUTCREATE) return ERR_OUTPUTCREATE;
		return ERR_SPLIT;
	}

	//videoEditor->remove();
}