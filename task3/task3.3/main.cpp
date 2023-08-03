#include"SDL.h"
#include<iostream>
#include"al.h"
#include"alc.h"

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/time.h"
}
using namespace std;

int quit=0;
int pause=0;
int state=0;
string mfile_path="../../../file/test.mp4";
string pfile_path="../../../file/test.pcm";

AVFormatContext* fctx;
AVCodecContext* dctx;
AVFrame* frame;
int video_index;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Event event;

ALCdevice* device;
ALCcontext* context;
ALuint source;
ALuint buffer;
float pitch = 1.0f;

int MP4(void *data) {
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
    
    SDL_Quit();
    return 0;
}

int PCM(void *data)
{
	device = alcOpenDevice(nullptr);
	if (!device) {
		cout << "device open error" << endl;
		return -1;
	}

	context = alcCreateContext(device, nullptr);
	if (!context) {
		cout << "context create error" << endl;
		alcCloseDevice(device);
		return -1;
	}

	alcMakeContextCurrent(context);

	alGenSources(1, &source);

	alGenBuffers(1, &buffer);

	FILE* fp = nullptr;
	fopen_s(&fp, pfile_path.c_str(), "rb");
	if (!fp) {
		cout << "file open error" << endl;
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* file_data = new char[file_size];
	fread(file_data, 1, file_size, fp);
	fclose(fp);

	alBufferData(buffer, AL_FORMAT_STEREO16, file_data, file_size, 44100);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
	while(!quit)
	{
        
	}

	free(file_data);
	alcMakeContextCurrent(NULL);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcDestroyContext(context);
	alcCloseDevice(device);
	SDL_Quit();
	return 0;
}

int main(int arc,char*argv[]){

    fctx = avformat_alloc_context();
    avformat_open_input(&fctx, mfile_path.c_str(), NULL, NULL);
    avformat_find_stream_info(fctx, NULL);

    av_dump_format(fctx, 0, mfile_path.c_str(), 0);

    video_index = av_find_best_stream(fctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
    AVCodecParameters* par = fctx->streams[video_index]->codecpar;
    dctx = avcodec_alloc_context3(NULL);
    avcodec_parameters_to_context(dctx, par);

    const AVCodec* codec = avcodec_find_decoder(dctx->codec_id);
    avcodec_open2(dctx, codec, NULL);
    frame = av_frame_alloc();

    int screen_w = par->width;
    int screen_h = par->height;

    window = SDL_CreateWindow("MP4 Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_w, screen_h,SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV,SDL_TEXTUREACCESS_STREAMING, screen_w, screen_h);
    SDL_CreateThread(PCM,"PCM",NULL);
    SDL_CreateThread(MP4,"MP4",NULL);
    SDL_Event event;

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
                pause=~pause;
                    if (pause)
				        alSourcePause(source);
			        else
				        alSourcePlay(source);
            }
            if (event.key.keysym.sym == SDLK_r) {
                alSourceRewind(source);
                alSourcePlay(source);
                av_seek_frame(fctx,video_index,0, AVSEEK_FLAG_BACKWARD);
            }
            if (event.key.keysym.sym == SDLK_w)
			{
                pitch += 0.1;
			    alSourcef(source, AL_PITCH, pitch);
            }
		    if (event.key.keysym.sym == SDLK_s)
			{
                pitch -= 0.1;
			    alSourcef(source, AL_PITCH, pitch);
            }
        }
    }
    return 0;
}