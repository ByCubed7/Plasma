// By @ByCubed7 on Twitter

#include "Audio.h"

Audio::Audio()
{
    std::uint8_t channels;
    std::int32_t sampleRate;
    std::uint8_t bitsPerSample;
    std::vector<char> soundData;
    /*
    if (!load_wav("iamtheprotectorofthissystem.wav", channels, sampleRate, bitsPerSample, soundData))
    {
        std::cerr << "ERROR: Could not load wav" << std::endl;
        return 0;
    }
    */

    alGenBuffers(1, &buffer);

    if      (channels == 1 && bitsPerSample == 8)   format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16)  format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8)   format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16)  format = AL_FORMAT_STEREO16;
    else
    {
        std::cerr
            << "ERROR: unrecognised wave format: "
            << channels << " channels, "
            << bitsPerSample << " bps" << std::endl;
        return;
    }

    alBufferData(buffer, format, soundData.data(), soundData.size(), sampleRate);
    //alCall(alBufferData, buffer, format, soundData.data(), soundData.size(), sampleRate);
    
    
    soundData.clear(); // erase the sound in RAM

    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcei(source, AL_BUFFER, buffer);

    alSourcePlay(source);

    state = AL_PLAYING;

    while (state == AL_PLAYING)
    {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }

    return;
}

Audio::~Audio()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    contextMadeCurrent = alcMakeContextCurrent(nullptr);
    alcDestroyContext(openALContext);

    ALCboolean closed;
    closed = alcCloseDevice(openALDevice);
}

void Audio::Prepare()
{
    alcOpenDevice(nullptr);
    //if (!openALDevice) return;

    openALContext = alcCreateContext(openALDevice, nullptr);

    contextMadeCurrent = alcMakeContextCurrent(openALContext);
}







void Audio::Devices(ALCdevice* device)
{
	const ALCchar* devicesChar = alcGetString(device, ALC_DEVICE_SPECIFIER);

	const char* ptr = devicesChar;

    devices.clear();

	do {
        devices.push_back(std::string(ptr));
		ptr += devices.back().size() + 1;
	} 
	while (*(ptr + 1) != '\0');
}

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

    // ..seb was here

}