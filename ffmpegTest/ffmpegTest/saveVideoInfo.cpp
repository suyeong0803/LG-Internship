#include "Editor.h"
//
//#include "json/include/json/json.h"
//#pragma comment(lib, "json/lib_json.lib")

/**
	@brief ���� ��¥ string���� ��ȯ

	@param t : struct tm*�� t ���� -> ���� ���� �ð�

	@return ��ȯ string
	@remark ���ǻ��� ����
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
	@brief vector�� json���� ��ȯ�� qt���� ���
	@param videoInfos : vector<videoInfo>�� videoInfo ����

	@return ����
	@remark ����
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
*	@brief  ���� ���� ����
	@detail ui�� �����ϱ� ���� ���� ���, ���� ���� �ð�, ���� ���� �ð�, ���� ���� �ð� ���� ����

	@param folderPath : string�� folderPath ���� -> ����ڰ� �Է��� ���� ���

	@return SUCCESS or ErrorCode
	@remark ���ǻ��� ����
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

		// ���� ��¥ ����
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

		// ���, ���� ���� �ð�, ���� ���� �ð�, ���� ��¥ 
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