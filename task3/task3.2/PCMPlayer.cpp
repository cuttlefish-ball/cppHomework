#include <al.h>
#include <alc.h>
#include <iostream>

using namespace std;

int main(int argc, char*argv[])
{
	ALCdevice* device = alcOpenDevice(nullptr);
	if (!device) {
		cout << "device open error" << endl;
		return -1;
	}

	ALCcontext* context = alcCreateContext(device, nullptr);
	if (!context) {
		cout << "context create error" << endl;
		alcCloseDevice(device);
		return -1;
	}

	alcMakeContextCurrent(context);

	ALuint source;
	alGenSources(1, &source);

	ALuint buffer;
	alGenBuffers(1, &buffer);

	string file = "C:\\Users\\吴雨澎\\Desktop\\公司\\c++Homework\\task3\\file\\test.pcm";
	FILE* fp = nullptr;
	fopen_s(&fp, file.c_str(), "rb");
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

	ALint state;
	bool pause = false, quit=false;
	float pitch = 1.0f;

	while(!quit)
	{
		int a=getchar();
		switch (a)
		{
		case ' ':
			pause = !pause;
			if (pause)
				alSourcePause(source);
			else
				alSourcePlay(source);
			break;
		case 'r':
			alSourceRewind(source);
			alSourcePlay(source);
			break;
		case 'w':
			pitch += 0.1;
			alSourcef(source, AL_PITCH, pitch);
			break;
		case 's':
			pitch -= 0.1;
			alSourcef(source, AL_PITCH, pitch);
			break;
		case 'q':
			quit = true;
		}
	}

	free(file_data);
	alcMakeContextCurrent(NULL);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcDestroyContext(context);
	alcCloseDevice(device);

	return 0;
}