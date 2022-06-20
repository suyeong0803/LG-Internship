<<<<<<< HEAD
#include "Editor.h"

/**
	@brief 시스템 콜로 호출하기 위한 파일 경로가 저장된 텍스트 파일을 만든다.

	@param startIndex : int형 startIndex 변수 -> 병합할 시작 인덱스
	@param endIndex : int형 endIndex 변수 -> 병합할 마지막 인덱스

	@return 리턴값 없음
	@remark 주의사항 없음
*/

void makeTXTFile(int startIndex, int endIndex) {
	std::ofstream writeFile("D:\\list.txt");
	for (int i = startIndex; i <= endIndex; i++)
	{
		writeFile << "file 'D:\\convert\\output_convert" + std::to_string(i) + ".mp4'";
		writeFile << std::endl;
	}
	writeFile.close();

}

/**
*	@brief 여러 개 파일 하나로 병합
	@detail 사용자가 원하는 구간에 따라 startIndex, endIndex를 찾고 병합
	-> system call 사용해 구현
	-> 원본 파일 자체의 pts, dts 값이 일정하게 증가하지 않아 직접 구현이 어려움
	-> 파일이 두 개 이상이 되면서 두 번째 파일의 첫번째 pts, dts 값이 첫번째 파일의 마지막 pts, dts보다 작아질 수 있어 병합에 오류 발생

	@param startTime : int64_t형 startTime 변수 -> 사용자가 입력한 시작 시간
	@param endTime : int64_t형 endTime 변수 -> 사용자가 입력한 종료 시간

	@return startIndex
	@remark 주의사항 없음
*/

int Editor::concat(int64_t startTime, int64_t endTime)
{
	int startIndex = -1, endIndex = -1;
	for (int i = 0; i < m_videoInfos.size(); i++)
	{
		if (startIndex != -1 && endIndex != -1) break;
		if (m_videoInfos[i].startTime <= startTime && startTime < m_videoInfos[i].endTime ) startIndex = i;
		if (m_videoInfos[i].startTime < endTime && endTime <= m_videoInfos[i].endTime) endIndex = i;
	}
	makeTXTFile(startIndex, endIndex);
	std::string command = "ffmpeg -f concat -safe 0 -i D:\\list.txt -c copy -safe 0 D:\\output_concat.mp4";
	system(command.c_str());
	std::cout << startIndex << " " << endIndex << std::endl;

	return startIndex;
}

//void concat(int startIndex, int endIndex)
//{
//	AVOutputFormat* ofmt = NULL;
//	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
//	int ret, i;
//
//	//int64_t last_pts = 0, last_dts = 0;
//	int64_t duration = 0;
//
//	std::string outputPath = "output_concat.mp4";
//	std::map<int, int64_t> durationPts, durationDts;
//	std::map<int, int64_t> last_pts, last_dts;
//
//	ifmt_ctx = NULL;
//	if ((ret = avformat_open_input(&ifmt_ctx, "convert\\output_convert0.mp4", 0, 0)) < 0)
//	{
//		fprintf(stderr, "Can't open file");
//		exit(-1);
//	}
//
//	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
//	{
//		fprintf(stderr, "fail to stream info");
//		exit(-1);
//	}
//
//	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, outputPath.c_str());
//
//	if (!ofmt_ctx)
//	{
//		fprintf(stderr, "can't create output");
//		exit(-1);
//	}
//
//	ofmt = ofmt_ctx->oformat;
//
//	AVStream* in_stream = NULL, * out_stream = NULL;
//	for (i = 0; i < ifmt_ctx->nb_streams; i++)
//	{
//		in_stream = ifmt_ctx->streams[i];
//		out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
//
//		if (!out_stream)
//		{
//			fprintf(stderr, "fail output stream");
//			exit(-1);
//		}
//
//		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
//		if (ret < 0)
//		{
//			fprintf(stderr, "fail to copy context");
//			exit(-1);
//		}
//
//		out_stream->codec->codec_tag = 0;
//		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
//			out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//	}
//
//	av_dump_format(ofmt_ctx, 0, outputPath.c_str(), 1);
//	if (!(ofmt->flags & AVFMT_NOFILE))
//	{
//		ret = avio_open(&ofmt_ctx->pb, outputPath.c_str(), AVIO_FLAG_WRITE);
//		if (ret < 0)
//		{
//			fprintf(stderr, "can't open output file");
//			exit(-1);
//		}
//	}
//
//	ret = avformat_write_header(ofmt_ctx, NULL);
//	if (ret < 0)
//	{
//		fprintf(stderr, "error opening output");
//		exit(-1);
//	}
//
//	for (int f = startIndex; f < endIndex; f++)
//	{
//		std::string filePath = "convert\\output_convert" + std::to_string(f) + ".mp4";
//		std::cout << filePath << std::endl;
//
//		ifmt_ctx = NULL;
//		if ((ret = avformat_open_input(&ifmt_ctx, filePath.c_str(), 0, 0)) < 0)
//		{
//			fprintf(stderr, "Can't open file");
//			exit(-1);
//		}
//		
//		if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
//		{
//			fprintf(stderr, "fail to stream info");
//			exit(-1);
//		}
//
//		av_dump_format(ifmt_ctx, 0, filePath.c_str(), 0);
//
//		/*avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, outputPath.c_str());
//
//		if (!ofmt_ctx)
//		{
//			fprintf(stderr, "can't create output");
//			exit(-1);
//		}*/
//
//		 //ofmt = ofmt_ctx->oformat;
//
//		for (i = 0; i < ifmt_ctx->nb_streams; i++)
//		{
//			in_stream = ifmt_ctx->streams[i];
//			/*out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
//
//			if (!out_stream)
//			{
//				fprintf(stderr, "fail output stream");
//				exit(-1);
//			}*/
//
//			/*ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
//			if (ret < 0)
//			{
//				fprintf(stderr, "fail to copy context");
//				exit(-1);
//			}*/
//
//			/*out_stream->codec->codec_tag = 0;
//			if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
//				out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;*/
//		}
//
//		av_dump_format(ofmt_ctx, 0, outputPath.c_str(), 1);
//		if (!(ofmt->flags & AVFMT_NOFILE))
//		{
//			ret = avio_open(&ofmt_ctx->pb, outputPath.c_str(), AVIO_FLAG_WRITE);
//			if (ret < 0)
//			{
//				fprintf(stderr, "can't open output file");
//				exit(-1);
//			}
//		}
//
//		ret = avformat_write_header(ofmt_ctx, NULL);
//		if (ret < 0)
//		{
//			fprintf(stderr, "error opening output");
//			exit(-1);
//		}
//
//		while (1)
//		{
//			AVPacket pkt = { 0 };
//			av_init_packet(&pkt);
//
//			ret = av_read_frame(ifmt_ctx, &pkt);
//			if (ret < 0) break;
//
//			in_stream = ifmt_ctx->streams[pkt.stream_index];
//			out_stream = ofmt_ctx->streams[pkt.stream_index];
//
//			pkt.duration = av_rescale_q((int64_t)pkt.duration, in_stream->time_base, out_stream->time_base);
//			pkt.pos = -1;
//
//			duration = pkt.duration;
//
//			pkt.pts = av_rescale_q_rnd(pkt.pts + last_pts[duration], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//			pkt.dts = av_rescale_q_rnd(pkt.dts + last_dts[duration], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//			
//			if (durationPts.find(duration) == durationPts.end()) durationPts.insert({ duration, pkt.pts });
//			else durationPts[duration] = pkt.pts;
//
//			if (durationDts.find(duration) == durationDts.end()) durationDts.insert({ duration, pkt.dts });
//			else durationDts[duration] = pkt.dts;
//
//			av_packet_rescale_ts(&pkt, in_stream->time_base, out_stream->time_base);
//
//			printf("last_pts : %lld / last_dts : %lld / pts : %lld / dts : %lld / duration : %lld\n", last_pts[duration], last_dts[duration], pkt.pts, pkt.dts, pkt.duration);
//
//			ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
//			if (ret < 0)
//			{
//				fprintf(stderr, "error muxing packet");
//				break;
//			}
//			av_free_packet(&pkt);
//		}
//		
//		std::map<int, int64_t>::iterator it;
//		for (it = durationPts.begin(); it != durationPts.end(); it++)
//			last_pts[it->first] = it->second + it->first;
//
//		for (it = durationDts.begin(); it != durationDts.end(); it++)
//			last_dts[it->first] = it->second + it->first;
//
//	}
//	av_write_trailer(ofmt_ctx);
//
//	avcodec_close(ofmt_ctx->streams[0]->codec);
//	av_freep(&ofmt_ctx->streams[0]->codec);
//	av_freep(&ofmt_ctx->streams[0]);
//
//	avio_close(ofmt_ctx->pb);
//	av_free(ofmt_ctx);
//}
=======
#include "concatFiles.h"

// output 파일 초기화 수정해야 함!

void concat(std::vector<videoInfo> folder)
{
	AVOutputFormat* ofmt = NULL;
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	int ret, i;

	int64_t last_pts = 0, last_dts = 0;
	int64_t duration = 0;
	for (int f = 0; f < folder.size(); f++)
	{
		std::cout << folder[f].m_path.c_str() << std::endl;
		
		ifmt_ctx = NULL;
		if ((ret = avformat_open_input(&ifmt_ctx, folder[f].m_path.c_str(), 0, 0)) < 0)
		{
			fprintf(stderr, "Can't open file");
			exit(-1);
		}

		if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
		{
			fprintf(stderr, "fail to stream info");
			exit(-1);
		}

		av_dump_format(ifmt_ctx, 0, folder[f].m_path.c_str(), 0);

		avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, "output.mp4");

		if (!ofmt_ctx)
		{
			fprintf(stderr, "can't create output");
			exit(-1);
		}

		ofmt = ofmt_ctx->oformat;

		AVStream* in_stream = NULL, * out_stream = NULL;
		for (i = 0; i < ifmt_ctx->nb_streams; i++)
		{
			in_stream = ifmt_ctx->streams[i];
			out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);

			if (!out_stream)
			{
				fprintf(stderr, "fail output stream");
				exit(-1);
			}

			ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
			if (ret < 0)
			{
				fprintf(stderr, "fail to copy context");
				exit(-1);
			}

			out_stream->codec->codec_tag = 0;
			if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
				out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
		}

		av_dump_format(ofmt_ctx, 0, "output.mp4", 1);
		if (!(ofmt->flags & AVFMT_NOFILE))
		{
			ret = avio_open(&ofmt_ctx->pb, "output.mp4", AVIO_FLAG_WRITE);
			if (ret < 0)
			{
				fprintf(stderr, "can't open output file");
				exit(-1);
			}
		}

		ret = avformat_write_header(ofmt_ctx, NULL);
		if (ret < 0)
		{
			fprintf(stderr, "error opening output");
			exit(-1);
		}

		// 8 = start time
		ret = av_seek_frame(ifmt_ctx, -1, NULL, AVSEEK_FLAG_ANY);
		if (ret < 0)
		{
			fprintf(stderr, "error seek");
			exit(-1);
		}

		int64_t pts = 0, dts = 0;
		last_pts += duration;
		last_dts += duration;

		while (1)
		{
			AVPacket pkt = { 0 };
			av_init_packet(&pkt);

			ret = av_read_frame(ifmt_ctx, &pkt);
			if (ret < 0) break;

			in_stream = ifmt_ctx->streams[pkt.stream_index];
			out_stream = ofmt_ctx->streams[pkt.stream_index];

			pts = pkt.pts;
			dts = pkt.dts;
			duration = pkt.duration;

			pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX)) + last_pts;
			pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX)) + last_dts;

			if (pkt.pts < 0) pkt.pts = 0;
			if (pkt.dts < 0) pkt.dts = 0;

			pkt.duration = av_rescale_q((int64_t)pkt.duration, in_stream->time_base, out_stream->time_base);
			pkt.pos = -1;

			printf("last_pts : %lld / pts : %lld / dts : %lld / duration : %lld\n", last_pts, pkt.pts, pkt.dts, pkt.duration);

			ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
			if (ret < 0)
			{
				fprintf(stderr, "error muxing packet");
				break;
			}
			av_free_packet(&pkt);

		}
		last_dts += dts;
		last_pts += pts;

		av_write_trailer(ofmt_ctx);
	}

	avcodec_close(ofmt_ctx->streams[0]->codec);
	av_freep(&ofmt_ctx->streams[0]->codec);
	av_freep(&ofmt_ctx->streams[0]);

	avio_close(ofmt_ctx->pb);
	av_free(ofmt_ctx);
}

>>>>>>> 11cd1f6bdb032eccbfb743d8e3f9b1a0d05968a5
