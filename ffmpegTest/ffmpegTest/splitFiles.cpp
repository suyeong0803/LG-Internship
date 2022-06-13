#include "splitFiles.h"

void split(int start_time, int end_time, std::string filePath)
{
	AVOutputFormat* ofmt = NULL;
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	int ret, i;

	if ((ret = avformat_open_input(&ifmt_ctx, filePath.c_str(), 0, 0)) < 0)
	{
		fprintf(stderr, "Can't open file");
		exit(-1);
	}

	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0)
	{
		fprintf(stderr, "fail to stream info");
		exit(-1);
	}

	av_dump_format(ifmt_ctx, 0, filePath.c_str(), 0);

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

		out_stream->time_base = in_stream->time_base;
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
	ret = av_seek_frame(ifmt_ctx, -1, start_time * AV_TIME_BASE, AVSEEK_FLAG_ANY);
	if (ret < 0)
	{
		fprintf(stderr, "error seek");
		exit(-1);
	}

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

		if (av_q2d(in_stream->time_base) * pkt.pts > end_time) {
			av_free_packet(&pkt);
			break;
		}

		if (start_from[pkt.stream_index] == 0)
		{
			int64_t dts = pkt.dts;
			int64_t pts = pkt.pts;
			int64_t min_ts = dts > pts ? pts : dts;
			start_from[pkt.stream_index] = min_ts < 0 ? 0 : min_ts;
		}

		pkt.pts = av_rescale_q_rnd(pkt.pts - start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts - start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

		pkt.duration = av_rescale_q((int64_t)pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;

		//printf("pts : %lld / dts : %lld / duration : %lld\n", pkt.pts, pkt.dts, pkt.duration);

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
}
