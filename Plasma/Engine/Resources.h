#pragma once

#include <map>
#include <string>

#include "../Library/glad.h"

#include "texture.h"
#include "shader.h"
#include "Font.h"


// A singleton that deals with Textures and Shaders. 
class Resources {
public:
	
	// █▀ █ █ ▄▀█ █▀▄ █▀▀ █▀█
	// ▄█ █▀█ █▀█ █▄▀ ██▄ █▀▄

	// All the shaders we have cached
	static std::map<std::string, Shader> Shaders;

	// Loads a shader from file loading vertex, fragment shader's source code. 
	// If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	
	// Retrieves a cached shader
	static Shader& GetShader(std::string name);
	

	//▀█▀ █▀▀ ▀▄▀ ▀█▀ █ █ █▀█ █▀▀
	// █  ██▄ █ █  █  █▄█ █▀▄ ██▄

	// All the textures we have cached
	static std::map<std::string, Texture2D> Textures;

	// Loads a texture
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	
	// Retrieves a cached texture
	static Texture2D& GetTexture(std::string name);
	

	// █▀▀ █▀█ █▄ █ ▀█▀
	// █▀  █▄█ █ ▀█  █ 

	// All the fonts we have cached
	static std::map<std::string, Font> Fonts;
	
	// Loads a font
	static Font LoadFont(const char* file, std::string name);
	
	// Retrieves a cached font
	static Font& GetFont(std::string name);

	// - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - -


	// Properly de-allocates all loaded resources
	// The deconstructor, basically
	static void Clear();

private:
	// Private constructor
	Resources() { }

	// Loads a shader from a file
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	// Loads a texture from a file
	static Texture2D LoadTextureFromFile(const char* file, bool alpha);

	// Loads a font from a file
	static Font LoadFontFromFile(const char* file, unsigned int fontSize);

	static unsigned int defaultFontSize;
};