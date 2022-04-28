// By @ByCubed7 on Twitter

#pragma once

#include "../Vector.h"

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
	class Buffer {
	public:
		Buffer(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
		~Buffer();

		ALuint id;
	};
}; 

