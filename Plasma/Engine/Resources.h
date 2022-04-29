// By @ByCubed7 on Twitter

#pragma once

#include "Vector.h"
#include "Render/Font.h"
#include "Render/Texture2D.h"
#include "Render/Shader.h"
#include "Tilemaps/Tilemap.h"
#include "Audio/Wav.h"

#include <glm/glm.hpp>
#include "TiledLibrary/TiledLoader.h"
#include <al.h>

#include <map>
#include <string>

// A singleton that deals with Textures and Shaders. 
class Resources {
public:	

	// █▀▀ █▀█ █▄ █ ▀█▀
	// █▀  █▄█ █ ▀█  █ 

	// All the fonts we have cached
	static std::map<std::string, Font> Fonts;
	
	// Loads a font
	static Font LoadFont(const std::string file, std::string name);
	
	// Retrieves a cached font
	static Font& GetFont(std::string name);


	// ▀█▀ █ █   █▀▀ █▀▄▀█ ▄▀█ █▀█
	//  █  █ █▄▄ ██▄ █ ▀ █ █▀█ █▀▀

	// All the fonts we have cached
	static std::map<std::string, Tilemaps::Tilemap> tilemaps;

	// Loads a font
	static Tilemaps::Tilemap LoadTilemap(const std::string file, std::string name);

	// Retrieves a cached tilemap
	static Tilemaps::Tilemap& GetTilemap(std::string name);

	// Audio

	static std::map<std::string, Wav> wavs;

	static Wav LoadWav(const std::string file, std::string name);

	static Wav GetWav(std::string name);

	// - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - -


	// Properly de-allocates all loaded resources
	// The deconstructor, basically
	static void Clear();

private:
	// Private constructor
	Resources() {}

	// Loads a font from a file
	static Font LoadFontFromFile(const std::string file, unsigned int fontSize);

	static unsigned int defaultFontSize;

	// Deals with TMX file tilesheet loading
	static Tiled::Loader tiled;

	// 
	static std::vector<char> LoadWavFromFile(const std::string file);
	static bool LoadWavHeader(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size);
};