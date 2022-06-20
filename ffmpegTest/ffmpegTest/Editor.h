/**
	@file Editor.h
	@brief video editor app
*/

#pragma once
extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
#include "libavcodec/avcodec.h"
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
#include "libavformat/avio.h"
#include "libavutil/log.h"
}

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <Windows.h>

#include "videoInfo.h"

#pragma warning(disable:4996)

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")

#define ERR_INPUTOPEN		-1		// input ������ ���� ���
#define ERR_STREAMINFO		-2		// ��Ʈ�� ������ ��� ���� ��Ŷ �б� ����
#define ERR_OUTPUTCREATE	-3		// output ������ ��������� ���� ��� (���� ��ΰ� ���� ���)
#define ERR_OUTPUTSTREAM	-4		// �̵�� ���Ͽ� output ��Ʈ�� �߰� ����
#define ERR_COPYCONTEXT		-5		// input�� codec context�� output�� ���� ����
#define ERR_OUTPUTOPEN		-6		// output ���ҽ��� ���� ����
#define ERR_WRITEHEADER		-7		// output ���Ͽ� ��Ʈ�� ��� �ۼ� ����
#define ERR_SEEKFRAME		-8		// ���ϴ� ������ ã�� ����
#define ERR_BESTSTREAM		-9		// ���Ͽ��� �ֻ��� ������ ã�� ����
#define ERR_PACKETALLOC		-10		// ��Ŷ �Ҵ� ����
#define ERR_COPYCODEC		-11		// codec�� ���� outstream�� ���� ����
#define ERR_EMPTYFOLDER		-12		// ������ ������ ���� ���
#define ERR_NOTEXIST		-13		// �߸��� ���� ����� ���
#define ERR_MAXFILES		-14		// ���� �� ���� ������ 50�� �̻��� ���
#define ERR_UNDEFINED		-999	// �� ��

#define ERR_SAVEINFO		-1001	// ����ڿ��� ���� ��ġ �����ֱ� ���� �ϳ��� ����
#define ERR_CONVERT			-1002
#define ERR_CONCAT			-1003
#define ERR_SPLIT			-1004

#define SUCCESS 0

class Editor
{
	// ����� �Է�
	std::string	m_inputPath;		// save
	int64_t m_startTime, m_endTime;	// concat
	std::string	m_outputPath;		// split

	// split ���
	int m_startIndex;

	std::vector<videoInfo> m_videoInfos;

public:
	Editor() {};
	~Editor() {};

	int saveInfo(std::string folderPath);
	int convert(std::string in_fileName, std::string out_fileName);

	int concat(int64_t startTime, int64_t endTime);
	int split(int64_t startIndex, int64_t startTime, int64_t endTime, std::string out_fileName);

	void remove();

	void setStartTime(int64_t startTime) { this->m_startTime = startTime; }
	int getStartTime() { return m_startTime; }

	void setEndTime(int64_t endTime) { this->m_endTime = endTime; }
	int getEndTime() { return m_endTime; }

	void setInputPath(std::string	inputPath) { this->m_inputPath = inputPath; }
	std::string getInputPath() { return m_inputPath; }

	void setOutputPath(std::string	outputPath) { this->m_outputPath = outputPath; }
	std::string getOutputPath() { return m_outputPath; }

	void setIndex(int64_t startIndex) { this->m_startIndex = startIndex; }
	int getIndex() { return m_startIndex; }

	videoInfo getInfo(int index)
	{
		return m_videoInfos[index];
	}

	int getInfoSize()
	{
		return m_videoInfos.size();
	}
};