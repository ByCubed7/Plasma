// By @ByCubed7 on Twitter

#include "Audio.h"

void Audio::AudioCallbackException(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
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
}