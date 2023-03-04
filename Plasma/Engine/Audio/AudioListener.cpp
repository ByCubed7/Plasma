// By @ByCubed7 on Twitter


//#define VERBOSE

#include "AudioListener.h"

#include "Audio.h"

namespace Audio
{
	Listener::Listener()
	{
		#ifdef VERBOSE
		std::cout << "\n[Listener::Ctor] Created Default Listener" << std::endl;
		#endif
		SetPosition(Vector2(0));
		SetVelocity(Vector2(0));

		ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	Listener::~Listener()
	{
	}
	void Listener::SetPosition(Vector2 position)
	{
		#ifdef VERBOSE
		std::cout << "[Listener::SetPosition] Setting Position" << std::endl;
		#endif
		this->position = position;
		alListener3f(AL_POSITION, velocity.x, velocity.y, 1.0f); // Set Z to 0?
	}
	void Listener::SetVelocity(Vector2 velocity)
	{
		#ifdef VERBOSE
		std::cout << "[Listener::SetVelocity] Setting Velocity" << std::endl;
		#endif
		this->velocity = velocity;
		alListener3f(AL_VELOCITY, velocity.x, velocity.y, 0);
	}
}