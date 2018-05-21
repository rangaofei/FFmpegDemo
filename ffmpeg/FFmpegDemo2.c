//
// Created by saka on 18-5-17.
//

#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>


void showErrMsg(int errNum, char *msg, size_t msgSize) {
    memset(msg, 0, msgSize);
    av_strerror(errNum, msg, msgSize);
    fprintf(stderr, "%s", msg);
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
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    //Open video file
    fileName = argv[1];

    if (argc < 2) {
        fprintf(stderr, "Please use FFmpegDemo1 <file> to open a video file");
        return -1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "there is something wrong with SDL_Init: %s", SDL_GetError());
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

    pWindow = SDL_CreateWindow(fileName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               pCodecCtx->width, pCodecCtx->height, SDL_WINDOW_SHOWN);
    if (NULL == pWindow) {
        fprintf(stderr, "there is something wrong with SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
//    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
//    SDL_RenderClear(pRenderer);
//    SDL_RenderPresent(pRenderer);

    SDL_Delay(1000);


    pFrame = av_frame_alloc();
    AVFrame *pFrameRGB = av_frame_alloc();
    if (pFrameRGB == NULL) {
        return -1;
    }
    unsigned char *buffer = NULL;
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGRA, pCodecCtx->width, pCodecCtx->height,
                                            AV_INPUT_BUFFER_PADDING_SIZE);
    buffer = (unsigned char *) av_malloc(numBytes * sizeof(unsigned char));

    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_BGRA, pCodecCtx->width,
                         pCodecCtx->height, AV_INPUT_BUFFER_PADDING_SIZE);

    struct SwsContext *sws_ctx = NULL;
    AVPacket packet;

    sws_ctx = sws_getContext(pCodecCtx->width,
                             pCodecCtx->height,
                             pCodecCtx->pix_fmt,
                             pCodecCtx->width,
                             pCodecCtx->height,
                             AV_PIX_FMT_BGRA,
                             SWS_BILINEAR,
                             NULL, NULL, NULL);


    void *pixels;
    int width, height, depth, pitch;
    width = pCodecCtx->width;
    height = pCodecCtx->height;
    pixels = calloc(width * height * 4, 1);
    pitch = width * 4;
    depth = 4 * 8;

    uint32_t rmask, gmask, bmask, amask;
    rmask = 0xFF000000;
    gmask = 0x00FF0000;
    bmask = 0x0000FF00;
    amask = 0x000000FF;
    SDL_Surface *pTmpSurface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask,
                                                        bmask,
                                                        amask);
    if (NULL == pTmpSurface) {
        fprintf(stderr, "there is something wrong with SDL_CreateRGBBuffer:%s", SDL_GetError());
        return -1;
    }
    SDL_Texture *pTexture = NULL;
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pTmpSurface);
//    pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (NULL == pTexture) {
        fprintf(stderr, "there is something wrong with SDL_CreateTextureFromSurface:%s", SDL_GetError());
        return -1;
    }
    dstRect.x = srcRect.x = 0;
    dstRect.y = srcRect.y = 0;
    dstRect.w = srcRect.w = width;
    dstRect.h = srcRect.h = height;


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
//                    SDL_RenderClear(pRenderer);
                for (int t = 0; t < pCodecCtx->height; t++) {
                    memcpy(pixels + t * width * 4, pFrameRGB->data[0] + t * pFrameRGB->linesize[0], width * 4);
                }
                SDL_UpdateTexture(pTexture, NULL, pixels, pitch);
                SDL_RenderCopy(pRenderer, pTexture, &srcRect, &dstRect);

                SDL_RenderPresent(pRenderer);

            }
        }
        av_packet_unref(&packet);
    }
    av_free(buffer);
    av_frame_unref(pFrameRGB);
    av_frame_unref(pFrame);
    av_free(pFrame);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);
    SDL_Quit();
    return 0;
}