#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>

void showErrMsg(int errNum, char *msg, size_t msgSize) {
    memset(msg, 0, msgSize);
    av_strerror(errNum, msg, msgSize);
    fprintf(stderr, "%s", msg);
}

void SavaFrame(AVFrame *pFrame, int width, int height, int frame) {
    FILE *pFile;
    char szFilename[32];
    int y;


    sprintf(szFilename, "frame%d.ppm", frame);
    pFile = fopen(szFilename, "wb");

    if (pFile == NULL) {
        return;
    }

    fprintf(pFile, "P6\n%d %d\n225\n", width, height);

    for (y = 0; y < height; y++)
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);
    fclose(pFile);
}


int main(int argc, char *argv[]) {

    AVCodecParameters *codecPar = NULL;
    AVFormatContext *pFormatCtx = NULL;
    int i;
    int errNum;
    char errMsg[400];
    const char *fileName;
    int videoStream = -1;
    AVCodecContext *pCodecCtx = NULL;
    AVCodec *pCodec = NULL;
    AVFrame *pFrame = NULL;

    //Open video file
    fileName = argv[1];

    if (argc < 2) {
        fprintf(stderr, "Please use FFmpegDemo1 <file> to open a video file");
        return -1;
    }

    if ((errNum = avformat_open_input(&pFormatCtx, fileName, NULL, NULL)) != 0) {
        showErrMsg(errNum, errMsg, 400);
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        showErrMsg(errNum, errMsg, 400);
        return -1;
    }

    av_dump_format(pFormatCtx, 0, fileName, 0);


    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            codecPar = pFormatCtx->streams[i]->codecpar;
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1) {
        return -1;
    }

    pCodec = avcodec_find_decoder(codecPar->codec_id);
    if (pCodec == NULL) {
        fprintf(stderr, "Unsupported codec!");
        return -1;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, codecPar);

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        return -1;
    }


    pFrame = av_frame_alloc();
    AVFrame *pFrameRGB = av_frame_alloc();
    if (pFrameRGB == NULL) {
        return -1;
    }
    unsigned char *buffer = NULL;
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height,
                                            AV_INPUT_BUFFER_PADDING_SIZE);
    buffer = (unsigned char *) av_malloc(numBytes * sizeof(unsigned char));

    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width,
                         pCodecCtx->height, AV_INPUT_BUFFER_PADDING_SIZE);

    struct SwsContext *sws_ctx = NULL;
    AVPacket packet;

    sws_ctx = sws_getContext(pCodecCtx->width,
                             pCodecCtx->height,
                             pCodecCtx->pix_fmt,
                             pCodecCtx->width,
                             pCodecCtx->height,
                             AV_PIX_FMT_RGB24,
                             SWS_BILINEAR,
                             NULL, NULL, NULL);
    i = 0;
    while (av_read_frame(pFormatCtx, &packet) >= 0) {
        if (packet.stream_index == videoStream) {
            if (avcodec_send_packet(pCodecCtx, &packet) != 0) {
                fprintf(stderr, "there is something wrong with avcodec_send_packet\n");
                av_packet_unref(&packet);
                continue;
            }

            if (avcodec_receive_frame(pCodecCtx, pFrame) == 0) {
                sws_scale(sws_ctx, (uint8_t
                          const *const *) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height,
                          pFrameRGB->data,
                          pFrameRGB->linesize);
                if (++i <= 50) {
                    SavaFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
                }
            }
        }
        av_packet_unref(&packet);
        if (i == 50) {
            break;
        }
    }
    av_free(buffer);
    av_frame_unref(pFrameRGB);
    av_frame_unref(pFrame);
    av_free(pFrame);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);
    return 0;
}