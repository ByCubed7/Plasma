// By @ByCubed7 on Twitter

//#define VERBOSE

#pragma once

#include "SpriteRenderer.h"
#include "Shader.h"

namespace Render
{
    SpriteRenderer::SpriteRenderer(Shader& shader) : Renderer(shader)
    {
        float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glBindVertexArray(vertexArrayObject);

        glGenBuffers(1, &verticeVBO);

        glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color)
    {
        // Prepare transformations
        shader.Use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position - size * pivot, 0.0f)); // translate
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
        model = glm::scale(model, glm::vec3(size, 1.0f)); // scale

        shader.SetMatrix4("model", model);

        // render textured quad
        shader.SetVector3f("spriteColor", color);

        // Set shadow render dims
        shader.SetVector2f("spriteSize", { size.x, size.y });

        // Texture Frame
        shader.SetInteger("index", frame);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}