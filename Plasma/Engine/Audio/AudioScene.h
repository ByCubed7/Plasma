// By @ByCubed7 on Twitter

#pragma once

#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"

#include <iostream>
#include <vector>
#include <string>

#include "../../Library/OpenAL/AL/al.h"
#include "../../Library/OpenAL/AL/alc.h"
#include "../Wav.h"


namespace Audio
{
	struct Scene
	{
		Scene();
		~Scene();

		std::vector<Buffer*> buffers;
		std::vector<Source*> sources;

		std::vector<std::string> devices;

		ALCdevice* openALDevice;
		ALCcontext* openALContext;

		Listener* defaultListener;

		void Prepare();

		std::vector<std::string> Devices(ALCdevice* device);

		Buffer* CreateBuffer(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
		Buffer* CreateBuffer(Wav wavFile);
		Source* CreateSource();

		//void AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device);
	};
}
