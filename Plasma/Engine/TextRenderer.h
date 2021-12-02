// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"

#include <map>

#include "../Library/glad.h"
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"
#include "font.h"

namespace Render
{
    /// <summary>
    /// A renderer class for rendering text displayed by a font loaded using the 
    /// FreeType library. A single font is loaded, processed into a list of Character
    /// items for later rendering.
    /// </summary>
    class TextRenderer : Renderer
    {
    public:
        // Constructor
        TextRenderer(Shader& shader);

        // Renders a string of text using the precompiled list of characters
        void RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot = { 0.5f, 0.5f }, glm::vec3 color = glm::vec3(1.0f));

    private:
        unsigned int verticeVBO;
    };
}