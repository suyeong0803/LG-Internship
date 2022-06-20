#include "Editor.h"

/**
	@brief 필요없는 파일 삭제-> 용량 차지 방지 위함
	@param 파라미터 없음
	@return 리턴값 없음
	@remark 주의사항 없음
*/

void Editor::remove()
{
	system("del D:\\output_concat.mp4");
	
	std::filesystem::remove("D:\\list.txt");
	std::filesystem::remove_all("D:\\convert");
	//std::filesystem::remove("D:\\output_concat.mp4");
}