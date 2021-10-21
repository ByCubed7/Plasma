#pragma once

#include "Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"


class TextRenderer
{
public:
    // Constructor (inits shaders/shapes)
    TextRenderer(Shader& shader);

    // Destructor
    ~TextRenderer();

    // Renders a defined quad textured with given sprite
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    // Render state
    Shader shader;
    Font font;

    unsigned int quadVAO;

    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

