#include "SDL.h"
#include <iostream>
using namespace std;

string filePath = "C:\\Users\\吴雨澎\\Desktop\\公司\\c++Homework\\task3\\file\\test.yuv";
const int w = 1500, h = 800;
const int pix_w = 1200, pix_h = 600, frameSize = pix_w * pix_h * 3 / 2;
unsigned char buffer[frameSize];

int main(int argc, char* argv[]) {
	if (argc == 2)
		filePath = argv[1];
	cout << filePath << endl;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow("YUV Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pix_w, pix_h);
	FILE* fp = NULL;
	if (fopen_s(&fp, filePath.c_str(), "rb+"))
	{
		cout << "找不到yuv文件" << endl;
		return -1;
	}
	SDL_Event event;
	int i = 1, pause = 1;
	while (i)
	{
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				i = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					//按空格暂停
				case SDLK_SPACE:
					pause *= -1;
					break;
					//按r重播
				case SDLK_r:
					fseek(fp, 0, SEEK_SET);
					break;
				default:
					break;
				}
			}
		}
		if (pause == 1)
		{
			fread(buffer, 1, frameSize, fp);
			SDL_UpdateTexture(texture, NULL, buffer, pix_w);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(40);
		}
	}
	fclose(fp);
	SDL_Quit();
	return 0;
}