// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"

class Shader;

namespace Render
{
    /// <summary>
    /// A renderer class for rendering text displayed by a font loaded using the 
    /// FreeType library. A single font is loaded, processed into a list of Character
    /// items for later rendering.
    /// </summary>
    class TextRenderer : public Renderer
    {
    public:
        // Constructor
        TextRenderer(Shader& shader);

        // Renders a string of text using the precompiled list of characters
        void RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot, glm::vec3 color);

    private:
        unsigned int verticeVBO;
    };
}