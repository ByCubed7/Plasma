// By @ByCubed7 on Twitter

#pragma once

#include "../Vector.h"

#include "OpenAL/al.h"
#include "OpenAL/alc.h"

#include <iostream>
#include <vector>
#include <string>

namespace Audio
{
	/// <summary>
	/// Base Audio Source class for dealing with audio sources
	/// </summary>
	class Buffer {
	public:
		Buffer(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
		~Buffer();

		ALuint id;
	};
}; 

