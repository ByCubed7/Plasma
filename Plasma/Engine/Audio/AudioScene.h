// By @ByCubed7 on Twitter

#pragma once

#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "Audio.h"
#include "Wav.h"

#include "al.h"

#include <iostream>
#include <vector>
#include <string>

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
