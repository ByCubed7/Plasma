// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include "../../Library/OpenAL/AL/al.h"
#include "../../Library/OpenAL/AL/alc.h"

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
		Source();
		~Source();

		/// <summary>
		/// Bind a buffer object to this source
		/// </summary>
		/// <param name="bufferId">- the pointer to the memory buffer.</param>
		void Bind(ALint bufferId);
		void Play();

		bool IsPlaying();

		ALuint id;

	private:
		float pitch, gain;
		Vector2 position, velocity;
		bool loop = false;
	};
}; 

