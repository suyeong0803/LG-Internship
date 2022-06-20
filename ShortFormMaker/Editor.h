//#pragma once
//extern "C"
//{
//#include "libavformat/avformat.h"
//#include "libavutil/mathematics.h"
//#include "libavcodec/avcodec.h"
//#include "libavutil/opt.h"
//#include "libavutil/time.h"
//#include "libswscale/swscale.h"
//#include "libavformat/avio.h"
//#include "libavutil/log.h"
//}

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

#include "videoInfo.h"

//#pragma warning(disable:4996)

//#pragma comment(lib, "avformat.lib")
//#pragma comment(lib, "avutil.lib")
//#pragma comment(lib, "avcodec.lib")
//#pragma comment(lib, "swscale.lib")

#define ERR_INPUTOPEN		-1		// input 파일이 없는 경우
#define ERR_STREAMINFO		-2		// 스트림 정보를 얻기 위한 패킷 읽기 실패
#define ERR_OUTPUTCREATE	-3		// output 파일이 만들어지지 않은 경우 (폴더 경로가 없는 경우)
#define ERR_OUTPUTSTREAM	-4		// 미디어 파일에 output 스트림 추가 실패
#define ERR_COPYCONTEXT		-5		// input의 codec context를 output에 복사 실패
#define ERR_OUTPUTOPEN		-6		// output 리소스에 접근 실패
#define ERR_WRITEHEADER		-7		// output 파일에 스트림 헤더 작성 실패
#define ERR_SEEKFRAME		-8		// 원하는 프레임 찾기 실패
#define ERR_BESTSTREAM		-9		// 파일에서 최상의 프레임 찾기 실패
#define ERR_PACKETALLOC		-10		// 패킷 할당 실패
#define ERR_COPYCODEC		-11		// codec의 내용 outstream에 복사 실패
#define ERR_EMPTYFOLDER		-12		// 폴더에 파일이 없을 경우
#define ERR_NOTEXIST		-13		// 잘못된 폴더 경로일 경우
#define ERR_UNDEFINED		-999	// 그 외

#define ERR_SAVEINFO		-1001	// 사용자에게 오류 위치 보여주기 위해 하나로 통합
#define ERR_CONVERT			-1002
#define ERR_CONCAT			-1003
#define ERR_SPLIT			-1004

#define SUCCESS 0

//class Editor
//{
//    // 사용자 입력
//    int64_t m_startTime, m_endTime;	// concat
//    std::string	m_outputPath;		// split

//    // split 사용
//    int m_startIndex;

//public:
//    static std::vector<videoInfo> m_folder;

//public:
//    Editor() {};
//    ~Editor() {};
//
//	int saveInfo(std::string filePath);
//	int convert(std::string in_fileName, std::string out_fileName);

//	int concat(int64_t startTime, int64_t endTime);
//	int split(int64_t startFile, int64_t startTime, int64_t endTime, std::string out_fileName);

//	void remove();

//	void setStartTime(int64_t startTime) { this->m_startTime = startTime; }
//	int getStartTime() { return m_startTime; }

//	void setEndTime(int64_t endTime) { this->m_endTime = endTime; }
//	int getEndTime() { return m_endTime; }

//	void setOutputPath(std::string	outputPath) { this->m_outputPath = outputPath; }
//	std::string getOutputPath() { return m_outputPath; }

//	void setIndex(int64_t startIndex) { this->m_startIndex = startIndex; }
//	int getIndex() { return m_startIndex; }
//};
