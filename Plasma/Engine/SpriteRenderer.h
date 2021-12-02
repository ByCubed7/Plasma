// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

namespace Render
{
    class SpriteRenderer : Renderer
    {
    public:
        // Constructor (inits shaders/shapes)
        SpriteRenderer(Shader& shader);

        // Renders a defined quad textured with given sprite
        void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));

    private:
        unsigned int verticeVBO;
    };
}