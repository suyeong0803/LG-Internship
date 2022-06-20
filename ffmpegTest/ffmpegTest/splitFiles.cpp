#include "Editor.h"

/**
*	@brief 병합 영상 분할
	@detail 구간별로 병합한 영상을 사용자가 지정한 구간에 따라 분할
	-> seek_frame으로 start 구간으로 이동해 packet에 저장
	-> 현재 pts가 end time보다 크다면 종료

	@param startIndex : int64_t형 startIndex 변수 -> 시작 인덱스 값
	@param startTime : int64_t형 startTime 변수 -> 사용자가 입력한 시작 시간
	@param endTime : int64_t형 endTime 변수 -> 사용자가 입력한 종료 시간
	@param out_fileName : string형 out_fileName 변수 -> 최종 결과물 저장 경로

	@return SUCCESS or ErrorCode
	@remark 주의사항 없음
*/

int Editor::split(int64_t startIndex, int64_t startTime, int64_t endTime, std::string out_fileName)
{
	AVOutputFormat* ofmt = NULL;
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	AVStream* in_stream = NULL, * out_stream = NULL;

	int ret, i, result = SUCCESS;
	int stream_mapping_size = 0;
	int64_t* start_from = NULL;

	/*
		사용자가 입력하는 startTime과 endTime은 전체 영상 기준으로 선택
		따라서 startTime부터 시작하는 파일을 만들기 위해서
		병합한 파일인 startIndex의 startTime에서 사용자가 입력한 startTime을 뺀다
	*/ 

	startTime = startTime - m_videoInfos[startIndex].startTime;
	endTime = endTime - m_videoInfos[startIndex].startTime;

	if ((ret = avformat_open_input(&ifmt_ctx, "D:\\output_concat.mp4", 0, 0)) < 0)
	{
		result = ERR_INPUTOPEN;
		goto end;
	}

	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
	{
		result = ERR_STREAMINFO;
		goto end;
	}

	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_fileName.c_str());

	if (!ofmt_ctx)
	{
		result = ERR_OUTPUTCREATE;
		goto end;
	}

	ofmt = ofmt_ctx->oformat;

	av_dump_format(ifmt_ctx, -1, NULL, 0);

	for (i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		in_stream = ifmt_ctx->streams[i];
		out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);

		if (!out_stream)
		{
			result = ERR_OUTPUTSTREAM;
			goto end;
		}

		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0)
		{
			result = ERR_COPYCONTEXT;
			goto end;
		}

		out_stream->time_base = in_stream->time_base;
		out_stream->codec->codec_tag = 0;
		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}

	if (!(ofmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&ofmt_ctx->pb, out_fileName.c_str(), AVIO_FLAG_WRITE);
		if (ret < 0)
		{
			result = ERR_OUTPUTOPEN;
			goto end;
		}
	}

	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0)
	{
		result = ERR_WRITEHEADER;
		goto end;
	}

	ret = av_seek_frame(ifmt_ctx, -1, startTime, AVSEEK_FLAG_ANY);
	if (ret < 0)
	{
		result = ERR_SEEKFRAME;
		goto end;
	}

	stream_mapping_size = 0;
	start_from = new int64_t(sizeof(int64_t) * ifmt_ctx->nb_streams);
	memset(start_from, NULL, sizeof(int64_t) * ifmt_ctx->nb_streams);
	while (1)
	{
		AVPacket pkt = { 0 };
		av_init_packet(&pkt);

		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0) { break; }

		in_stream = ifmt_ctx->streams[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];

		if (av_q2d(in_stream->time_base) * pkt.pts > endTime) {
			av_free_packet(&pkt);
			break;
		}

		// 자른 위치부터 start time을 잡기 위해 start_from 값 조정
		if (start_from[pkt.stream_index] == 0)
		{
			int64_t dts = pkt.dts;
			int64_t pts = pkt.pts;
			int64_t min_ts = dts > pts ? pts : dts;
			start_from[pkt.stream_index] = min_ts < 0 ? 0 : min_ts;
		}

		// pts, dts에 start_from 값을 빼서 output 파일의 시간 조정
		pkt.pts = av_rescale_q_rnd(pkt.pts - start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts - start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

		pkt.duration = av_rescale_q((int64_t)pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;

		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (ret < 0)
			break;

		av_free_packet(&pkt);
	}

	av_write_trailer(ofmt_ctx);

end:
	avformat_close_input(&ifmt_ctx);

	/* close output */
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
		avio_closep(&ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);

	return result;
}
