// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"
#include "Texture2D.h"

class Shader;
class Texture2D;

namespace Render
{
    class SpriteRenderer : public Renderer
    {
    public:
        // Constructor (inits shaders/shapes)
        SpriteRenderer(Shader& shader);

        // Renders a defined quad textured with given sprite
        void drawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color);

    private:
        unsigned int verticeVBO;
    };
}