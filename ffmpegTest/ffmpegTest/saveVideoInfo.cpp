extern "C"
{
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libavcodec/avcodec.h"
#include "libavutil/log.h"
}

#include <iostream>
#include <string>
#include <filesystem>

#include <sys/stat.h>
#include <time.h>

#include <vector>

#include "videoInfo.h"

#pragma warning(disable:4996)

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

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

int main()
{
	std::string path = "D:\\00000003REC";
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		std::string f = file.path().string();
		const char* szFilePath = f.c_str();

		int ret;
		AVFormatContext* m_context = NULL;

		ret = avformat_open_input(&m_context, szFilePath, NULL, NULL);
		if (ret != 0)
		{
			av_log(NULL, AV_LOG_ERROR, "File [%s] Open Fail (ret %d)\n", szFilePath, ret);
			exit(-1);
		}
		av_log(NULL, AV_LOG_INFO, "File [%s] Open Success\n", szFilePath);

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
		else {
			printf("%s\n", szFilePath);
			printf("\tTime Creation     : %s\n", timeToString(localtime(&buf.st_ctime)));
			printf("\tTime Last Written : %s\n", timeToString(localtime(&buf.st_mtime)));
			printf("\tTime Last Access  : %s\n", timeToString(localtime(&buf.st_atime)));

			createDate = timeToString(localtime(&buf.st_mtime));
		}

		ret = avformat_find_stream_info(m_context, NULL);
		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "File [%s] Open Stream Fail (ret %d)\n", szFilePath, ret);
			exit(-1);
		}

		AVCodec* vcodec = NULL;
		ret = av_find_best_stream(m_context, AVMEDIA_TYPE_VIDEO, -1, -1, &vcodec, 0);
		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "File [%s] Open best stream Fail (ret %d)\n", szFilePath, ret);
			exit(-1);
		}

		const int idx = ret;
		AVStream* vstrm = m_context->streams[idx];

		videoInfo video = { szFilePath, av_rescale_q(vstrm->duration, vstrm->time_base, { 1,1000 }) / 1000., createDate };
		std::cout << video.m_duration << std::endl;


		folder.push_back(video);
		std::cout << std::endl;
	}
	
	sort(folder.begin(), folder.end(), compare);
	for (int i = 0; i < folder.size(); i++) std::cout << folder[i].m_path <<" " << folder[i].m_duration << " " << folder[i].m_createDate << std::endl;
}