// By @ByCubed7 on Twitter

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../../Library/OpenAL/AL/al.h"
#include "../../Library/OpenAL/AL/alc.h"

struct Audio
{

	Audio();
	~Audio();

	std::vector<std::string> devices;


	ALCdevice* openALDevice;
	ALCcontext* openALContext;
	ALCboolean contextMadeCurrent = false;
	ALuint buffer;
	ALenum format;
	ALuint source;
	ALint state;

	unsigned int source;

	void Prepare();

	void Devices(ALCdevice* device);

	void AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device);
}; 

