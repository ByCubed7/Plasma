// By @ByCubed7 on Twitter

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../../Library/OpenAL/AL/al.h"
#include "../../Library/OpenAL/AL/alc.h"

struct Audio
{
	ALCcontext* openALContext;

	void Prepare();

	bool Devices(std::vector<std::string>& devicesVec, ALCdevice* device);

	void AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device);
}; 

