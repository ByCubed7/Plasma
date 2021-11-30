// By @ByCubed7 on Twitter

#pragma once

#include <map>
#include <string>

#include "../Library/glad.h"
#include "../Library/TiledLibrary/TiledLoader.h"

#include "Font.h"
#include "Tilemaps/Tilemap.h"
#include "texture.h"
#include "shader.h"

using namespace std;


// A singleton that deals with Textures and Shaders. 
class Resources {
public:
	
	// █▀ █ █ ▄▀█ █▀▄ █▀▀ █▀█
	// ▄█ █▀█ █▀█ █▄▀ ██▄ █▀▄

	// All the shaders we have cached
	static map<string, Shader> Shaders;

	// Loads a shader from file loading vertex, fragment shader's source code. 
	// If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, string name);
	
	// Retrieves a cached shader
	static Shader& GetShader(string name);
	

	//▀█▀ █▀▀ ▀▄▀ ▀█▀ █ █ █▀█ █▀▀
	// █  ██▄ █ █  █  █▄█ █▀▄ ██▄

	// All the textures we have cached
	static map<string, Texture2D> Textures;

	// Loads a texture
	static Texture2D LoadTexture(const std::string file, bool alpha, string name);
	
	// Retrieves a cached texture
	static Texture2D& GetTexture(string name);
	

	// █▀▀ █▀█ █▄ █ ▀█▀
	// █▀  █▄█ █ ▀█  █ 

	// All the fonts we have cached
	static map<string, Font> Fonts;
	
	// Loads a font
	static Font LoadFont(const std::string file, string name);
	
	// Retrieves a cached font
	static Font& GetFont(string name);


	// ▀█▀ █ █   █▀▀ █▀▄▀█ ▄▀█ █▀█
	//  █  █ █▄▄ ██▄ █ ▀ █ █▀█ █▀▀

	// All the fonts we have cached
	static map<string, Tilemaps::Tilemap> tilemaps;

	// Loads a font
	static Tilemaps::Tilemap LoadTilemap(const std::string file, string name);

	// Retrieves a cached tilemap
	static Tilemaps::Tilemap& GetTilemap(string name);

	// - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - -


	// Properly de-allocates all loaded resources
	// The deconstructor, basically
	static void Clear();

private:
	// Private constructor
	Resources() {}

	// Loads a shader from a file
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	// Loads a texture from a file
	static Texture2D LoadTextureFromFile(const std::string file, bool alpha);

	// Loads a font from a file
	static Font LoadFontFromFile(const std::string file, unsigned int fontSize);

	static unsigned int defaultFontSize;

	// Deals with TMX file tilesheet loading
	static Tiled::Loader tiled;
};