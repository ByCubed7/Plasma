#include <map>
#include <string>

#include "Library/glad.h"

#include "texture.h"
#include "shader.h"


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
	static std::map<std::string, Texture2D> Textures;
	
	// Loads a font
	static void LoadFont(const char* file, std::string name);
	
	// Retrieves a cached font
	static void GetFont(std::string name);

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
	static void LoadTextureFromFile(const char* file);
};

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};