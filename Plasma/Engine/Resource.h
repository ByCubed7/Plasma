// By @ByCubed7 on Twitter

#pragma once

#include "Vector2.h"
#include "Render/Font.h"
#include "Render/texture.h"
#include "Render/shader.h"
#include "Tilemaps/Tilemap.h"
#include "Audio/Wav.h"

#include "glad.h"
#include <al.h>
#include "TiledLibrary/TiledLoader.h"

#include <map>
#include <string>

template<class T>
class Resource {
public:
	// All the shaders we have cached
	static std::map<std::string, T> cache;

	// Loads from file.
	static T LoadShader(std::string name);

	// Retrieves a cached.
	static T& GetShader(std::string name);
};