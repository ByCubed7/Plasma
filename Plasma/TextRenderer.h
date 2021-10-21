#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include "Library/glad.h"
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"
#include "font.h"


// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
    // Holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    
    // Shader used for text rendering
    Shader TextShader;
    
    // Constructor
    TextRenderer(unsigned int width, unsigned int height);
    
    // Pre-compiles a list of characters from the given font
    void Load(std::string font, unsigned int fontSize);
    
    // Renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
    // render state
    unsigned int VAO, VBO;
};

#endif 