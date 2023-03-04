// By @ByCubed7 on Twitter

#pragma once

#include "Audio/Wav.h"

#include "OpenAL/AL/al.h"
#include "OpenAL/AL/alc.h"

#include <map>
#include <string>

// A singleton that deals with Textures and Shaders. 
class Resources {
public:	

	// Audio

	static std::map<std::string, Wav> wavs;

	static Wav LoadWav(const std::string file, std::string name);

	static Wav GetWav(std::string name);

	// - - - - - - - - - - - - - - - - - - - - - - - -

private:
	// Private constructor
	Resources() {}

	// 
	static std::vector<char> LoadWavFromFile(const std::string file);
	static bool LoadWavHeader(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size);
};