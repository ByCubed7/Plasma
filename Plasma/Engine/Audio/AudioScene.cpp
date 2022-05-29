// By @ByCubed7 on Twitter

//#define VERBOSE

#include "AudioScene.h"

namespace Audio
{
	Scene::Scene()
	{
		#ifdef VERBOSE
		std::cout << "[Scene::Ctor] Created Scene" << std::endl;
		#endif
		openALContext = 0;
		openALDevice = 0; 
		
		#ifdef VERBOSE
		std::cout << "[Scene::Ctor] Creating Listener" << std::endl;
		#endif
		defaultListener = new Listener();
	}

	Scene::~Scene()
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::Dtor] Deleting Scene" << std::endl;
		std::cout << "[Audio::Scene::Dtor] Deleting defaultListener" << std::endl;
		#endif
		delete defaultListener;
		
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::Dtor] Deleting " << sources.size() << " sources." << std::endl;
		#endif
		for (auto& source : sources) delete source;
		
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::Dtor] Deleting " << buffers.size() << " buffers." << std::endl;
		#endif
		for (auto& buffer : buffers) delete buffer;

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(openALContext);

		alcCloseDevice(openALDevice);
	}

	void Scene::Prepare()
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::Prepare]" << std::endl;
		std::cout << "\t- Preparing..." << std::endl;
		#endif
		/// Specify explicitely which device to open by using its name instead of nullptr.
		openALDevice = alcOpenDevice(nullptr);
		openALContext = alcCreateContext(openALDevice, nullptr);

		#ifdef VERBOSE
		if (openALContext) std::cout << "\t- Successfully created openALContext!" << std::endl;
		else  std::cout << "\t- Failed to create openALContext!" << std::endl;
		#endif
		
		
		#ifdef VERBOSE
		std::cout << "\t- Making openALContext the current context!" << std::endl;
		#endif
		alcMakeContextCurrent(openALContext);

		
		#ifdef VERBOSE
		std::cout << std::endl;
		#endif
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

	Buffer* Scene::CreateBuffer(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq)
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::CreateBuffer] Creating Buffer" << std::endl;
		#endif
		Audio::Buffer* buf = new Buffer(format, data, size, freq);
		buffers.push_back(buf);
		return buf;
	}
	Buffer* Scene::CreateBuffer(Wav wavFile) { return CreateBuffer(wavFile.Format(), wavFile.Data(), wavFile.Size(), wavFile.sampleRate); }

	Source* Scene::CreateSource()
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Scene::CreateSource] Creating Source" << std::endl;
		#endif
		Source* source = new Source(openALDevice);
		sources.push_back(source);
		return source;
	}

	/*
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

	}*/
}