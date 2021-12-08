// By @ByCubed7 on Twitter

#include "AudioSource.h"

namespace Audio
{
	Source::Source()
	{
		alGenSources(1, &id);

		pitch = 1; 
		gain = 1;
		position = Vector2::zero;
		velocity = Vector2::zero;
		loop = false;
	}

	Source::~Source()
	{
		alDeleteSources(1, &id);
	}
	void Source::Bind(ALint bufferId) { alSourcei(id, AL_BUFFER, bufferId); }
	void Source::Play()	{ alSourcePlay(id); }

	bool Source::IsPlaying()
	{
		ALint state;
		alGetSourcei(id, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}
}