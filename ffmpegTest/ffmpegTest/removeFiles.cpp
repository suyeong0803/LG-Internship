#include "Editor.h"

/**
	@brief �ʿ���� ���� ����-> �뷮 ���� ���� ����
	@param �Ķ���� ����
	@return ���ϰ� ����
	@remark ���ǻ��� ����
*/

void Editor::remove()
{
	system("del D:\\output_concat.mp4");
	
	std::filesystem::remove("D:\\list.txt");
	std::filesystem::remove_all("D:\\convert");
	//std::filesystem::remove("D:\\output_concat.mp4");
}