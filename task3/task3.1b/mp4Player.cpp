#include<iostream>
#include<SDL.h>
#include<SDL_thread.h>
extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/time.h"
}

using namespace std;

string filePath = "../../../file/test.mp4";

AVFormatContext* fctx;
AVCodecContext* dctx;
AVFrame* frame;
int video_index;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;

int quit = 0;
int pause = 0;

int demixAndDecode(void* data) {
    AVPacket pkt;

    int ret = 0;

    while (!quit)
    {
        if (pause) {
            SDL_Delay(10);
            continue;
        }
        ret = av_read_frame(fctx, &pkt);
        if (ret<0)
        {
            cout << "packet error" << endl;
            break;
        }

        if (pkt.stream_index == video_index)
        {
            ret = avcodec_send_packet(dctx, &pkt);
            if (ret < 0)
            {
                cout << "send pakcet error" << endl;
                break;
            }

            while (ret >= 0)
            {
                ret = avcodec_receive_frame(dctx, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0)
                {
                    cout << "receive error" << endl;
                    break;
                }
                else
                {
                    SDL_UpdateYUVTexture(texture, NULL,
                        frame->data[0], frame->linesize[0],
                        frame->data[1], frame->linesize[1],
                        frame->data[2], frame->linesize[2]);

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(40);
                    av_frame_unref(frame);
                }
            }
        }
        av_packet_unref(&pkt);
    }
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
    return 0;
}


int main(int argc, char* argv[]) {
    if (argc == 2)
        filePath = argv[1];
    fctx = avformat_alloc_context();
    avformat_open_input(&fctx, filePath.c_str(), NULL, NULL);
    avformat_find_stream_info(fctx, NULL);

    av_dump_format(fctx, 0, filePath.c_str(), 0);

    video_index = av_find_best_stream(fctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    AVCodecParameters* par = fctx->streams[video_index]->codecpar;
    dctx = avcodec_alloc_context3(NULL);
    avcodec_parameters_to_context(dctx, par);

    const AVCodec* codec = avcodec_find_decoder(dctx->codec_id);
    avcodec_open2(dctx, codec, NULL);
    frame = av_frame_alloc();

    int screen_w = par->width;
    int screen_h = par->height;

    window = SDL_CreateWindow("MP4 Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_w, screen_h-100,
        SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV,SDL_TEXTUREACCESS_STREAMING, screen_w, screen_h);
    
    SDL_Thread* demixThread = SDL_CreateThread(demixAndDecode, "demix", NULL);
    
    while (1)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            quit = 1;
            break;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE) {
                pause = ~pause;
            }
            if (event.key.keysym.sym == SDLK_r) {
                av_seek_frame(fctx,video_index,0, AVSEEK_FLAG_BACKWARD);
            }
        }
    }
    SDL_Quit();
    return 0;
}