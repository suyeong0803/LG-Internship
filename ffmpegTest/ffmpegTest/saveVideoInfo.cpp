#include "Editor.h"
//
//#include "json/include/json/json.h"
//#pragma comment(lib, "json/lib_json.lib")

/**
	@brief 생성 날짜 string으로 변환

	@param t : struct tm*형 t 변수 -> 파일 생성 시간

	@return 변환 string
	@remark 주의사항 없음
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

/**
	@brief vector를 json으로 변환해 qt에서 사용
	@param videoInfos : vector<videoInfo>형 videoInfo 변수

	@return 없음
	@remark 없음
*/
void toJson(std::vector<videoInfo> videoInfos)
{
	/*Json::Value root(Json::arrayValue);

	for (size_t i = 0; i != videoInfos.size(); i++)
	{
		Json::Value obj(Json::objectValue);
		obj["m_path"] = videoInfos[i].m_path;
		obj["m_startTime"] = videoInfos[i].startTime;
		obj["m_endTime"] = videoInfos[i].endTime;

		root.append(obj);
	}*/

}

/**
*	@brief  영상 정보 저장
	@detail ui와 소통하기 위해 영상별 경로, 누적 시작 시간, 누적 종료 시간, 파일 생성 시간 정보 저장

	@param folderPath : string형 folderPath 변수 -> 사용자가 입력한 폴더 경로

	@return SUCCESS or ErrorCode
	@remark 주의사항 없음
*/
int Editor::saveInfo(std::string folderPath)
{
	int64_t startTime = 0;
	AVFormatContext* m_context = NULL;
	AVCodec* vcodec = NULL;

	int result = SUCCESS;

	if (!std::filesystem::exists(folderPath)) return ERR_NOTEXIST;
	if (std::filesystem::is_empty(folderPath)) return ERR_EMPTYFOLDER;

	int fileCnt = 0;
	for (const auto& file : std::filesystem::directory_iterator(folderPath))
	{
		fileCnt++;
		if (fileCnt > 50) return ERR_MAXFILES;
	}

	for (const auto& file : std::filesystem::directory_iterator(folderPath))
	{
		m_context = NULL;
		vcodec = NULL;

		std::string f = file.path().string();
		const char* szFilePath = f.c_str();

		int ret;
		ret = avformat_open_input(&m_context, szFilePath, NULL, NULL);
		if (ret != 0)
		{
			result = ERR_INPUTOPEN;
			goto end;
		}

		// 생성 날짜 저장
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
		{
			result = ERR_STREAMINFO;
			goto end;
		}

		ret = av_find_best_stream(m_context, AVMEDIA_TYPE_VIDEO, -1, -1, &vcodec, 0);
		if (ret < 0)
		{
			result = ERR_BESTSTREAM;
			goto end;
		}

		const int idx = ret;
		AVStream* vstrm = m_context->streams[idx];

		int64_t duration = av_rescale_q(vstrm->duration , vstrm->time_base, { 1,90000 });

		// 경로, 누적 시작 시간, 누적 종료 시간, 생성 날짜 
		videoInfo video = { szFilePath, startTime, startTime + duration, createDate };
		m_videoInfos.push_back(video);

		startTime += duration;
	}

	sort(m_videoInfos.begin(), m_videoInfos.end(), compare);
	toJson(m_videoInfos);

end:
	avformat_close_input(&m_context);
	av_free(m_context);
	av_free(vcodec);

	return result;
}