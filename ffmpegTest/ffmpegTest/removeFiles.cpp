#include "Editor.h"

/*
	
	필요없는 파일 삭제
	-> 용량 차지 방지 위함

*/

void Editor::remove()
{
	std::filesystem::remove("D:\\list.txt");
	std::filesystem::remove_all("D:\\convert");
	std::filesystem::remove("D:\\output_concat.mp4");
}