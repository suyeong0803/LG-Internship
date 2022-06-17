#include "Editor.h"

/*

	구간별로 병합한 영상을 사용자가 지정한 구간에 따라 분할
	-> seek_frame으로 start 구간으로 이동해 packet에 저장
	-> 현재 pts가 end time보다 크다면 종료

*/

int Editor::split(int64_t startIndex, int64_t startTime, int64_t endTime, std::string out_fileName)
{
	AVOutputFormat* ofmt = NULL;
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	int ret, i;

	startTime = startTime - m_folder[startIndex].startTime;
	endTime = endTime - m_folder[startIndex].startTime;

	std::cout << startTime << std::endl;

	if ((ret = avformat_open_input(&ifmt_ctx, "D:\\output_concat.mp4", 0, 0)) < 0)
		return ERR_INPUTOPEN;

	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
		return ERR_STREAMINFO;

	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_fileName.c_str());

	if (!ofmt_ctx)
		return ERR_OUTPUTCREATE;

	ofmt = ofmt_ctx->oformat;

	av_dump_format(ifmt_ctx, -1, NULL, 0);

	AVStream* in_stream = NULL, * out_stream = NULL;
	for (i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		in_stream = ifmt_ctx->streams[i];
		out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);

		if (!out_stream)
			return ERR_OUTPUTSTREAM;

		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0)
			return ERR_COPYCONTEXT;

		out_stream->time_base = in_stream->time_base;
		out_stream->codec->codec_tag = 0;
		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}

	if (!(ofmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&ofmt_ctx->pb, out_fileName.c_str(), AVIO_FLAG_WRITE);
		if (ret < 0)
			return ERR_OUTPUTOPEN;
	}

	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0)
		return ERR_WRITEHEADER;

	ret = av_seek_frame(ifmt_ctx, -1, startTime, AVSEEK_FLAG_ANY);
	if (ret < 0)
		return ERR_SEEKFRAME;

	int stream_mapping_size = 0;
	int64_t* start_from = new int64_t(sizeof(int64_t) * ifmt_ctx->nb_streams);
	memset(start_from, NULL, sizeof(int64_t) * ifmt_ctx->nb_streams);
	while (1)
	{
		AVPacket pkt = { 0 };
		av_init_packet(&pkt);

		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0) break;

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

		printf("%lld %lld\n", pkt.pts, pkt.dts);

		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (ret < 0)
		{
			fprintf(stderr, "error muxing packet");
			break;
		}
		av_free_packet(&pkt);

	}

	av_write_trailer(ofmt_ctx);

	avcodec_close(ofmt_ctx->streams[0]->codec);
	av_freep(&ofmt_ctx->streams[0]->codec);
	av_freep(&ofmt_ctx->streams[0]);

	avio_close(ofmt_ctx->pb);
	av_free(ofmt_ctx);

	return SUCCESS;
}
