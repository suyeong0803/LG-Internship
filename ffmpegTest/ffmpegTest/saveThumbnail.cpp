#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}
  // <-- Requiered for av_image_get_buffer_size

#pragma warning (disable:4996)

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

//gcc a.c -o a.o `pkg-config --cflags --libs libavformat libavcodec libswresample libswscale libavutil` && ./a.o

void ProcessArray(char* singleLine, int length)
{
    for (int i = 0; i < length; i++)
    {
        singleLine[i];
    }
}

void save_gray_frame(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
{
    FILE* f;
    int i;
    printf("\n\nWrap: %d\n\n", wrap);
    f = fopen(filename, "w");
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
    for (i = 0; i < ysize; i++)
    {
        unsigned char* ch = (buf + i * wrap);
        ProcessArray((char*)ch, xsize);
        fwrite(ch, 1, xsize, f);
    }
    fclose(f);
}


void save_rgb_frame(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
{
    FILE* f;
    int i;
    f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", xsize, ysize);

    for (i = 0; i < ysize; i++)
    {
        unsigned char* ch = (buf + i * wrap);
        //ProcessArray(ch, xsize);
        fwrite(ch, 1, xsize * 3, f);  //Write 3 bytes per pixel.
    }

    fclose(f);
}



int decode_packet(AVPacket* packet, AVCodecContext* codecContext, AVFrame* frame, AVFrame* pFrameRGB, struct SwsContext* sws_ctx)
{
    int response = avcodec_send_packet(codecContext, packet);
    if (response < 0)
    {
        printf("Error sending packet to decoder");
        return response;
    }
    while (response >= 0)
    {
        response = avcodec_receive_frame(codecContext, frame);
        if (response == AVERROR(EAGAIN))
        {   //Not data memory for frame, have to free and get more data
            av_frame_unref(frame);
            av_freep(frame);
            break;
        }
        if (response == AVERROR_EOF)
        {
            printf("Error AVERROR_EOF");
            break;
        }
        else if (response < 0)
        {
            //printf("Error receiving frame: %s", av_err2str(response));
            av_frame_unref(frame);
            av_freep(frame);
            return response;
        }
        if (response >= 0)
        {
            printf(" Frame %d(type = %c, size = %d bytes, format = %d) pts %ld keyFrame %d [DTS %d]",
                codecContext->frame_number, av_get_picture_type_char(frame->pict_type),
                frame->pkt_size, frame->format, frame->pts, frame->key_frame, frame->coded_picture_number);

            //int numBytes = (frame->pkt_size) * 3;

            response = sws_scale(sws_ctx, (unsigned char const* const*)(frame->data), (frame->linesize),
                0, codecContext->height, pFrameRGB->data, pFrameRGB->linesize);

            if (response <= 0)
            {
                printf("Error: sws_scale status = %d\n", response);
            }

            //unsigned char *bu = malloc(numBytes);
            char frame_filename[1024];
            snprintf(frame_filename, sizeof(frame_filename), "%s-%d.ppm", "frame", codecContext->frame_number);
            if (frame->format != AV_PIX_FMT_YUV420P)
            {
                printf("Maybe not grayscale generated");
            }
            //save_gray_frame(frame->data[0],frame->linesize[0],frame->width,frame->height, frame_filename);

            //Write RBG output to PPM image file
            save_rgb_frame(pFrameRGB->data[0], pFrameRGB->linesize[0], pFrameRGB->width, pFrameRGB->height, frame_filename);
        }

    }
}



int main()
{
    // D:\\00000003REC\\000000030000000aSTRDEC0.tp
    const char* fileName = "cloud.mov";
    AVFormatContext* formatContext = avformat_alloc_context();
    struct SwsContext* sws_ctx = NULL;

    if (!formatContext)
    {
        printf("Error allocating memory for format context");
        return -1;
    }

    if (avformat_open_input(&formatContext, fileName, NULL, NULL) != 0)
    {
        printf("Error: Unable to open file");
        return -1;
    }
    printf("Format: %s, duration %ld, bitrate: %ld\n", formatContext->iformat->name,
        formatContext->duration, formatContext->bit_rate);

    if (avformat_find_stream_info(formatContext, NULL) < 0)
    {
        printf("Error: Unable to get stream info");
        return -1;
    }

    AVCodec* codec = NULL;
    AVCodecParameters* codecParameters = NULL;
    int videoStreamIndex = -1;
    for (int i = 0; i < formatContext->nb_streams; i++)
    {
        AVCodecParameters* localCodecParameters = NULL;
        localCodecParameters = formatContext->streams[i]->codecpar;
        printf("Time base before open coded %d %d\n", formatContext->streams[i]->time_base.num, formatContext->streams[i]->time_base.den);
        printf("Frame rate before open coded %d %d\n", formatContext->streams[i]->r_frame_rate.num, formatContext->streams[i]->r_frame_rate.den);
        printf("Start time %d", formatContext->streams[i]->start_time);
        printf("\nDuration %d", formatContext->streams[i]->duration);

        AVCodec* localCodec = NULL;
        localCodec = avcodec_find_decoder(localCodecParameters->codec_id);
        if (localCodec == NULL)
        {
            printf("Error: Unsupported codec");
            continue;
        }
        if (localCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            if (videoStreamIndex == -1)
            {
                videoStreamIndex = i;
                codec = localCodec;
                codecParameters = localCodecParameters;
            }
            printf("Video Resolution: %d %d", localCodecParameters->width, localCodecParameters->height);
        }
        else if (localCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            printf("Audio: %d channels, sample rate %d", localCodecParameters->channels, localCodecParameters->sample_rate);
        }
        printf("\nCodec :%s ID %d bit_rate %ld", localCodec->name, localCodec->id, localCodecParameters->bit_rate);
    }

    if (videoStreamIndex == -1)
    {
        printf("Error: File does not contain video stream");
        return -1;
    }

    AVCodecContext* codecContext = avcodec_alloc_context3(codec);
    if (!codecContext)
    {
        printf("Failed to allocate memory for AVCodecContext");
        return -1;
    }

    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0)
    {
        printf("Failed to copy codec paramters to codec context");
        return -1;
    }

    if (avcodec_open2(codecContext, codec, NULL) < 0)
    {
        printf("failed to open codec throught avcodec_open2");
    }

    AVFrame* frame = av_frame_alloc();
    if (!frame)
    {
        printf("Failed to allocate moemory for AVFrame");
        return -1;
    }
    AVPacket* packet = av_packet_alloc();
    if (!packet)
    {
        printf("Failed to allocate memory for AVPacket");
        return -1;
    }

    int response = 0;
    int howManypacketsToProcess = 8;
    int frameFinished = 0;

    sws_ctx = sws_getContext
    (
        codecContext->width,
        codecContext->height,
        codecContext->pix_fmt,
        codecContext->width,
        codecContext->height,
        AV_PIX_FMT_RGB24,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL
    );


    ///////////////////////////////////////////////////////////////////////////
    AVFrame* pFrameRGB = av_frame_alloc();

    //int num_bytes = avpicture_get_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height); //https://stackoverflow.com/questions/12831761/how-to-resize-a-picture-using-ffmpegs-sws-scale
    //avpicture_fill((AVPicture*)pFrameRGB, frame_buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height);  //deprecated use av_image_fill_arrays() instead.

    int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 1); //https://stackoverflow.com/questions/35678041/what-is-linesize-alignment-meaning

    unsigned char* frame_buffer = (uint8_t*)av_malloc(num_bytes);

    response = av_image_fill_arrays(pFrameRGB->data,       //uint8_t *dst_data[4], 
        pFrameRGB->linesize,   //int dst_linesize[4],
        frame_buffer,          //const uint8_t * src,
        AV_PIX_FMT_RGB24,      //enum AVPixelFormat pix_fmt,
        codecContext->width,   //int width, 
        codecContext->height,  //int height,
        1);                    //int align);

    if (response < 0)
    {
        printf("av_image_fill_arrays Failed, response = %d\n", response);
    }

    pFrameRGB->width = codecContext->width;
    pFrameRGB->height = codecContext->height;
    ///////////////////////////////////////////////////////////////////////////


    while (av_read_frame(formatContext, packet) >= 0)
    {
        if (packet->stream_index == videoStreamIndex)
        {
            printf("\nAVPacket->pts %d", packet->pts);
            response = decode_packet(packet, codecContext, frame, pFrameRGB, sws_ctx);
            if (response < 0)
            {
                printf("\nError response < 0\n");
                break;
            }
            if (--howManypacketsToProcess <= 0)
            {
                break;
            }
        }
        av_packet_unref(packet);
    }

    av_free(frame_buffer);

    return 0;
}