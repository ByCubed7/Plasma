// By @ByCubed7 on Twitter

# define VERBOSE

#include "AudioSource.h"

namespace Audio
{
	Source::Source(ALCdevice* device)
	{
		this->device = device;

		#ifdef VERBOSE
		std::cout << "[Audio::Source::Ctor]" << std::endl;
		#endif
		
		alGenSources(1, &id);
		#ifdef VERBOSE
		std::cout << "\t- Created Source " << id << std::endl;
		#endif

		#ifdef VERBOSE
		std::cout << std::endl;
		#endif

		SetPitch(1);
		SetGain(1);
		SetPosition(Vector2::zero);
		SetVelocity(Vector2::zero);
		SetLoop(false);
	}
	Source::~Source()
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Source::Dtor]" << std::endl;
		std::cout << "\t- Deleting Source " << id << std::endl;
		#endif
		alDeleteSources(1, &id);
	}

	void Source::Bind(ALint bufferId) 
	{ 
		#ifdef VERBOSE
		std::cout << "[Audio::Source::Bind]" << std::endl;
		std::cout << "\t- Binding Buffer " << id << std::endl;
		#endif
		alSourcei(id, AL_BUFFER, bufferId); 
	}
	void Source::Play()	
	{ 
		#ifdef VERBOSE
		std::cout << "[Audio::Source::Play]" << std::endl;
		std::cout << "\t- Playing Source " << id << std::endl;
		#endif
		alSourcePlay(id);

		#ifdef VERBOSE
		ALCenum err = alcGetError(device);
		if (err != ALC_NO_ERROR) std::cout << "\t- Error " << err << "!";
		#endif

		#ifdef VERBOSE
		std::cout << std::endl;
		#endif
	}

	bool Source::IsPlaying()
	{
		ALint state;
		alGetSourcei(id, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	void Source::SetPitch(float pitch)
	{
		this->pitch = pitch;
		alSourcef(id, AL_PITCH, pitch);
	}

	void Source::SetGain(float gain)
	{
		this->gain = gain;
		alSourcef(id, AL_GAIN, gain);
	}

	void Source::SetPosition(Vector2 position)
	{
		this->position = position;
		alSource3f(id, AL_POSITION, position.x, position.y, 0);
	}

	void Source::SetVelocity(Vector2 velocity)
	{
		this->velocity = velocity;
		alSource3f(id, AL_VELOCITY, velocity.x, velocity.y, 0);
	}

	void Source::SetLoop(bool isLooping)
	{
		loop = isLooping;
		alSourcei(id, AL_LOOPING, loop);
	}





}