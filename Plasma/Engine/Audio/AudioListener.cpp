// By @ByCubed7 on Twitter

#include "AudioListener.h"

namespace Audio
{
	Listener::Listener()
	{
		position = Vector2::zero;
		velocity = Vector2::zero;

		ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	Listener::~Listener()
	{
	}
	void Listener::SetPosition(Vector2 position)
	{
		this->position = position;
		alListener3f(AL_POSITION, position.x, position.y, 1.0f); // Set Z to 0?
	}
	void Listener::SetVelocity(Vector2 velocity)
	{
		this->velocity = velocity;
		alListener3f(AL_VELOCITY, velocity.x, velocity.y, 0);
	}
}