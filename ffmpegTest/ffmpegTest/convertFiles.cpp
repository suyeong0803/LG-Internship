#include "Editor.h"

/*

    ����ڿ��� ������ �����ֱ� ���� ��ü ���� ��ȯ
    -> ���� ������ �״�� mpeg2�� �ΰ� �����̳ʸ� mpeg4�� ��ȯ
    -> ���� ������� mpeg4�� ��ȯ�ϰ� �Ǹ� �ð��� ���� �ɸ��� �뷮�� Ŀ��

*/

int Editor::convert(std::string in_fileName, std::string out_fileName)
{
    const AVOutputFormat* ofmt = NULL;
    AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
    AVPacket* pkt = NULL;
    int ret, i;
    int stream_index = 0;
    int* stream_mapping = NULL;
    int stream_mapping_size = 0;

    pkt = av_packet_alloc();
    if (!pkt) 
        return ERR_PACKETALLOC;

    if ((ret = avformat_open_input(&ifmt_ctx, in_fileName.c_str(), 0, 0)) < 0) 
        return ERR_INPUTOPEN;


    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) 
        return ERR_STREAMINFO;
    
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_fileName.c_str());
    if (!ofmt_ctx) 
        return ERR_OUTPUTCREATE;

    stream_mapping_size = ifmt_ctx->nb_streams;
    stream_mapping = new int(stream_mapping_size * sizeof(*stream_mapping));
    if (!stream_mapping) {
        ret = AVERROR(ENOMEM);
        return -1;
    }

    ofmt = ofmt_ctx->oformat;

    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        AVStream* out_stream;
        AVStream* in_stream = ifmt_ctx->streams[i];
        AVCodecParameters* in_codecpar = in_stream->codecpar;

        if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
            in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
            in_codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
            stream_mapping[i] = -1;
            continue;
        }

        stream_mapping[i] = stream_index++;

        out_stream = avformat_new_stream(ofmt_ctx, NULL);
        if (!out_stream) 
            return ERR_OUTPUTSTREAM;

        ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
        if (ret < 0) 
            return ERR_COPYCODEC;
       
        out_stream->codecpar->codec_tag = 0;
    }

    if (!(ofmt->flags & AVFMT_NOFILE)) {
        ret = avio_open(&ofmt_ctx->pb, out_fileName.c_str(), AVIO_FLAG_WRITE);
        if (ret < 0) 
            return ERR_OUTPUTOPEN;
    }

    ret = avformat_write_header(ofmt_ctx, NULL);
    if (ret < 0) 
        return ERR_WRITEHEADER;

    while (1) {

        av_init_packet(pkt);
        AVStream* in_stream, * out_stream;

        ret = av_read_frame(ifmt_ctx, pkt);
        if (ret < 0)
            break;

        in_stream = ifmt_ctx->streams[pkt->stream_index];
        if (pkt->stream_index >= stream_mapping_size ||
            stream_mapping[pkt->stream_index] < 0) {
            av_packet_unref(pkt);
            continue;
        }

        pkt->stream_index = stream_mapping[pkt->stream_index];
        out_stream = ofmt_ctx->streams[pkt->stream_index];

        /*
        �� ������ start_time ���� 0�� �ƴ� ���� ���� ��ü�� start_time ���� ����
        -> pts, dts ���� 0�� �������� ������ ��ȯ ������ ���� start_time�� �� ������ start_time���� ��
        -> pts, dts ��ü�� 0�� �����ϸ� ��Ŷ�� ���� ������ ������ pts, dts�� 0�� �Ǳ� ������ ������ ���ܼ� �����
        -> pts, dts�� ��Ŷ�� ���޵� input stream�� start_time�� ���� ���
        */ 
        pkt->pts = av_rescale_q_rnd(pkt->pts - in_stream->start_time, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt->dts = av_rescale_q_rnd(pkt->dts - in_stream->start_time, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

        pkt->pos = -1;

        ret = av_interleaved_write_frame(ofmt_ctx, pkt);
        if (ret < 0) {
            printf("Error muxing packet\n");
            break;
        }
    }

    av_write_trailer(ofmt_ctx);
    //end:
    //    av_packet_free(&pkt);
    //
    //    avformat_close_input(&ifmt_ctx);
    //
    //    /* close output */
    //    if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
    //        avio_closep(&ofmt_ctx->pb);
    //    avformat_free_context(ofmt_ctx);
    //
    //    av_freep(&stream_mapping);
    //
    //    if (ret < 0 && ret != AVERROR_EOF) {
    //        printf("Error occurred: %d\n", ret);
    //        return 1;
    //    }

    return SUCCESS;
}