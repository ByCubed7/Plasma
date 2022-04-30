// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"
#include "../Resource.h"

#include <glm/glm.hpp>

#include <map>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};


struct Font : Resource<Font>
{
	std::map<char, Character> Characters;

	void AddCharacter(char c, Character character);
	Character GetCharacter(char c);

protected:
    static unsigned int defaultFontSize;

    Font FromFile(const std::string filename) override;
    void Clear() override;
};