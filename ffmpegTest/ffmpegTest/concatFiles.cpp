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

