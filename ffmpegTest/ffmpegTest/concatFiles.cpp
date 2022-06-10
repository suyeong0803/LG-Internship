#include <stdio.h>
#include <iostream>
#include <string>
#include <filesystem>

#include <vector>

#include"videoInfo.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/mem.h"
}



#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

char* timeToString(struct tm* t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
	);

	return s;
}

void saveVideoInfo()
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

		folder.push_back(video);
	}
}

int main(int argc, char* argv[])
{
    AVStream*        m_iVstream = NULL;
    AVFormatContext* m_oFcontext;
    AVStream*        m_oVstream;

    avcodec_register_all();
    av_register_all();

	int ret;
	AVFormatContext* m_iFcontext = NULL;

	/*const char* filePath[15][256];
	std::string path = "D:\\00000003REC";
	int i = 0;

	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		std::string f = file.path().string();
		filePath[i] = f.c_str();
		std::cout << i << " : " << filePath[i++] << std::endl;
	}*/

	saveVideoInfo();

	/*for (int i = 0; i < 13; i++) 
		std::cout << i << " : " << filePath[i] << std::endl;*/

	ret = avformat_open_input(&m_iFcontext, folder[0].m_path.c_str(), NULL, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "could not open input file\n");
		exit(-1);
	}

	ret = avformat_find_stream_info(m_iFcontext, NULL);
	if (ret < 0)
	{
		fprintf(stderr, "could not find stream info\n");
		exit(-1);
	}


	for (unsigned int i = 0; i < m_iFcontext->nb_streams; i++)
	{
		if (m_iFcontext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_iVstream = m_iFcontext->streams[i];
			break;
		}
	}


	if (m_iVstream == NULL)
	{
		fprintf(stderr, "didn't find any video stream\n");
		exit(-1);
	}

	avformat_alloc_output_context2(&m_oFcontext, NULL, NULL, "output.mp4");


	m_oVstream = avformat_new_stream(m_oFcontext, 0);
	AVCodecContext* c = m_oVstream->codec;


	c->bit_rate = 400000;
	c->codec_id = m_iVstream->codec->codec_id;
	c->codec_type = m_iVstream->codec->codec_type;
	c->time_base.num = m_iVstream->time_base.num;
	c->time_base.den = m_iVstream->codec->time_base.den;
	c->width = m_iVstream->codec->width;
	c->height = m_iVstream->codec->height;
	c->pix_fmt = m_iVstream->codec->pix_fmt;
	c->flags = m_iVstream->codec->flags;
	c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	c->me_range = m_iVstream->codec->me_range;
	c->max_qdiff = m_iVstream->codec->max_qdiff;

	c->qmin = m_iVstream->codec->qmin;
	c->qmax = m_iVstream->codec->qmax;

	c->qcompress = m_iVstream->codec->qcompress;

	c->extradata = m_iVstream->codec->extradata;
	c->extradata_size = m_iVstream->codec->extradata_size;
	

	//avio_open(&m_oFcontext->pb, NULL, AVIO_FLAG_WRITE);

	//avformat_write_header(m_oFcontext, NULL);

	int last_pts = 0;
	int last_dts = 0;

	for (int i = 0; i < folder.size(); i++)
	{
		std::cout << i << std::endl;
		m_iFcontext = NULL;
		if (avformat_open_input(&m_iFcontext, folder[i].m_path.c_str(), NULL, NULL) != 0)
		{
			fprintf(stderr, "could not open input file\n");
			return -1;
		}

		if (avformat_find_stream_info(m_iFcontext, NULL) < 0)
		{
			fprintf(stderr, "could not find stream\n");
			return -1;
		}
		av_dump_format(m_iFcontext, 0, folder[i].m_path.c_str(), 0);

		m_iVstream = NULL;
		for (unsigned s = 0; s < m_iFcontext->nb_streams; s++)
		{
			if (m_iFcontext->streams[s]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				m_iVstream = m_iFcontext->streams[s];
				break;
			}
		}
		if (m_iVstream == NULL)
		{
			fprintf(stderr, "didn't find any video stream\n");
			return -1;
		}

		int64_t pts, dts;

		while (1)
		{
			AVPacket m_iPkt;
			av_init_packet(&m_iPkt);
			m_iPkt.size = 0;
			m_iPkt.data = NULL;

			if (av_read_frame(m_iFcontext, &m_iPkt) < 0) break;
			std::cout << m_iPkt.size << std::endl;

			m_iPkt.flags |= AV_PKT_FLAG_KEY;

			pts = m_iPkt.pts;
			m_iPkt.pts += last_pts;

			dts = m_iPkt.dts;
			m_iPkt.dts += last_dts;

			m_iPkt.stream_index = 0;

			static int num = 1;
			printf("frame %d\n", num++);

			av_interleaved_write_frame(m_oFcontext, &m_iPkt);
		}
		last_dts += dts;
		last_pts += pts;

		avformat_close_input(&m_iFcontext);
	}

	av_write_trailer(m_oFcontext);
	avcodec_close(m_oFcontext->streams[0]->codec);
	av_freep(&m_oFcontext->streams[0]->codec);
	av_freep(&m_oFcontext->streams[0]);

	avio_close(m_oFcontext->pb);
	av_free(m_oFcontext);

	return 0;
}