// By @ByCubed7 on Twitter

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../../Library/OpenAL/AL/al.h"
#include "../../Library/OpenAL/AL/alc.h"


namespace Audio
{
	struct Scene
	{

		Scene();
		~Scene();

		std::vector<std::string> devices;


		ALCdevice* openALDevice;
		ALCcontext* openALContext;

		unsigned int source;


		void Prepare();

		std::vector<std::string> Devices(ALCdevice* device);

		void AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device);
	};
}
