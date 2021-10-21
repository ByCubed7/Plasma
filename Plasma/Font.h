#pragma once
#include <map>

#include "Library/glad.h"

#include "texture.h"
#include "shader.h"


struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

struct Font
{
	std::map<char, Character> Characters;

	void AddCharacter(char c, Character character);
	Character GetCharacter(char c);
};