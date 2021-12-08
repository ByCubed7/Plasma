// By @ByCubed7 on Twitter

#include "AudioScene.h"


namespace Audio
{
	Scene::Scene()
	{
		openALContext = 0;
		openALDevice = 0;
		source = 0;
	}

	Scene::~Scene()
	{
		alDeleteSources(1, &source);

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(openALContext);

		alcCloseDevice(openALDevice);
	}

	void Scene::Prepare()
	{
		/// Specify explicitely which device to open by using its name instead of nullptr.
		alcOpenDevice(nullptr);
		//if (!openALDevice) return;

		openALContext = alcCreateContext(openALDevice, nullptr);

		alcMakeContextCurrent(openALContext);
	}



	std::vector<std::string> Scene::Devices(ALCdevice* device)
	{
		const ALCchar* devicesChar = alcGetString(device, ALC_DEVICE_SPECIFIER);

		const char* ptr = devicesChar;

		devices.clear();

		do {
			devices.push_back(std::string(ptr));
			ptr += devices.back().size() + 1;
		} while (*(ptr + 1) != '\0');

		return devices;
	}

	void Scene::AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
	{
		ALCenum error = alcGetError(device);
		if (error != ALC_NO_ERROR)
		{
			std::cout << "---------------" << std::endl;
			std::cout << "Debug message (" << error << "): " << filename << " | " << line << std::endl;
			switch (error)
			{
			case ALC_INVALID_VALUE:		std::cerr << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function"; break;
			case ALC_INVALID_DEVICE:	std::cerr << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function"; break;
			case ALC_INVALID_CONTEXT:	std::cerr << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";	break;
			case ALC_INVALID_ENUM:		std::cerr << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function"; break;
			case ALC_OUT_OF_MEMORY:		std::cerr << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function"; break;
			default:					std::cerr << "UNKNOWN ALC ERROR: " << error;
			} std::cout << std::endl;
			return;
		}
		return;

		// ..seb was here

	}
}