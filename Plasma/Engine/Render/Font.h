// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"
#include "Renderable.h"
#include "../Resource.h"

#include <map>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   getSize;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};


struct Font : Resource<Font>
{
	std::map<char, Character> Characters;

	void AddCharacter(char c, Character character);
	Character GetCharacter(char c);

    std::string text;

    void Render(std::string text, int vao, glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color);

protected:
    static unsigned int defaultFontSize;

    Font fromFile(const std::string filename) override;
    void clear() override;

    //// Renderable
    //unsigned int verticeVBO;
    //void LoadRenderer();
    //void UnloadRenderer();
};