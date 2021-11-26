// By @ByCubed7 on Twitter

#pragma once

#include <map>

#include "../Library/glad.h"
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"
#include "font.h"


// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
// TODO: 
// - Merge into one renderer class.
// - Move the loading and cacheing into the resources task.
class TextRenderer
{
public:    
    // Constructor
    TextRenderer(Shader& shader);
    ~TextRenderer();
        
    // Renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot = {0.5f, 0.5f}, glm::vec3 color = glm::vec3(1.0f));

private:
    // Shader used for text rendering
    Shader TextShader;

    // render state
    unsigned int VAO, VBO;
}; 