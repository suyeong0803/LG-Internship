#include "Editor.h"

/*
	
	ui와 소통하기 위해 영상별 정보 저장
	-> 경로, 누적 시작 시간, 누적 종료 시간, 파일 생성 시간
	
*/

char* timeToString(struct tm* t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
	);

	return s;
}

bool compare(videoInfo a, videoInfo b)
{
	return a.m_createDate < b.m_createDate;
}

int Editor::saveInfo(std::string filePath)
{
	int64_t startTime = 0;

	if (std::filesystem::is_empty(filePath)) return ERR_EMPTYFOLDER;
	if (!std::filesystem::exists(filePath)) return ERR_NOTEXIST;

	for (const auto& file : std::filesystem::directory_iterator(filePath))
	{
		std::string f = file.path().string();
		const char* szFilePath = f.c_str();

		int ret;
		AVFormatContext* m_context = NULL;

		ret = avformat_open_input(&m_context, szFilePath, NULL, NULL);
		if (ret != 0)
			exit(ERR_INPUTOPEN);

		struct _stat buf;
		std::string createDate;
		if (_stat(szFilePath, &buf) != 0) {
			switch (errno) {
			case ENOENT:
				fprintf(stderr, "File %s not found.\n", szFilePath); break;
			case EINVAL:
				fprintf(stderr, "Invalid parameter to _stat.\n"); break;
			default:
				fprintf(stderr, "Unexpected error in _stat.\n");
			}
		}
		else 
			createDate = timeToString(localtime(&buf.st_mtime));

		ret = avformat_find_stream_info(m_context, NULL);
		if (ret < 0)
			return ERR_STREAMINFO;

		AVCodec* vcodec = NULL;
		ret = av_find_best_stream(m_context, AVMEDIA_TYPE_VIDEO, -1, -1, &vcodec, 0);
		if (ret < 0)
			return ERR_BESTSTREAM;

		const int idx = ret;
		AVStream* vstrm = m_context->streams[idx];

		int64_t duration = av_rescale_q(vstrm->duration , vstrm->time_base, { 1,90000 });
		videoInfo video = { szFilePath, startTime, startTime + duration, createDate };
		m_folder.push_back(video);

		startTime += duration;
	}

	sort(m_folder.begin(), m_folder.end(), compare);
	return SUCCESS;
}