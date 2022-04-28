// By @ByCubed7 on Twitter

#pragma once

#include "../Vector.h"

#include "al.h"
#include "alc.h"

#include <iostream>
#include <vector>
#include <string>

namespace Audio
{
	/// <summary>
	/// Base Audio Source class for dealing with audio sources
	/// </summary>
	class Source {
	public:

		Source(ALCdevice* device);
		~Source();

		/// <summary>
		/// Bind a buffer object to this source
		/// </summary>
		/// <param name="bufferId">- the pointer to the memory buffer.</param>
		void Bind(ALint bufferId);
		void Play();

		bool IsPlaying();

		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetPosition(Vector2 position);
		void SetVelocity(Vector2 velocity);
		void SetLoop(bool isLooping);

		ALuint Id() { return id; }

	private:

		ALCdevice* device;
		ALuint id;

		float pitch, gain;
		Vector2 position, velocity;
		bool loop = false;
	};
};

