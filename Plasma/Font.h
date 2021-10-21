#pragma once
#include <map>

#include "Library/glad.h"

#include "texture.h"
#include "shader.h"


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};


struct Font
{
	std::map<char, Character> Characters;

	void AddCharacter(char c, Character character);
	Character GetCharacter(char c);
};