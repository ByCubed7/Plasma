// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"
#include "Renderable.h"
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


struct Font : Resource<Font>, Renderable<Font>
{
	std::map<char, Character> Characters;

	void AddCharacter(char c, Character character);
	Character GetCharacter(char c);

    std::string text;

protected:
    static unsigned int defaultFontSize;

    Font FromFile(const std::string filename) override;
    void Clear() override;

    // Renderable
    unsigned int verticeVBO;
    void LoadRenderer() override;
    void UnloadRenderer() override;

    void Render(glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color) override;
};