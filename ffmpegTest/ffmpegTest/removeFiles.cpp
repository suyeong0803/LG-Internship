#include "Editor.h"

/*
	
	�ʿ���� ���� ����
	-> �뷮 ���� ���� ����

*/

void Editor::remove()
{
	std::filesystem::remove("D:\\list.txt");
	std::filesystem::remove_all("D:\\convert");
	std::filesystem::remove("D:\\output_concat.mp4");
}