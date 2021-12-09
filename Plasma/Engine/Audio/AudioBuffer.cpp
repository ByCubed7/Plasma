// By @ByCubed7 on Twitter

//# define VERBOSE

#include "AudioBuffer.h"

namespace Audio
{
	Buffer::Buffer(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq)
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Buffer::Ctor]" << std::endl;
		#endif
		id = 0;
		alGenBuffers(1, &id);
		#ifdef VERBOSE
		std::cout << "\t- Created Buffer " << id << std::endl;
		#endif

		alBufferData(id, format, data, size, freq);		
		#ifdef VERBOSE
		std::cout << "\t- Handed Buffer data = "
			<< "[  Format: "<< format
			<< " | Data: " << data 
			<< " | Size: " << size 
			<< " | Freq: " << freq 
			<< "  ]" << std::endl;
		#endif
		
		#ifdef VERBOSE
		std::cout << std::endl;
		#endif
	}
	Buffer::~Buffer()
	{
		#ifdef VERBOSE
		std::cout << "[Audio::Buffer::Dtor]" << std::endl;
		std::cout << "\t- Deleting Buffer " << id << std::endl;
		#endif
		alDeleteBuffers(1, &id);
		
		#ifdef VERBOSE
		std::cout << std::endl;
		#endif
	}
}