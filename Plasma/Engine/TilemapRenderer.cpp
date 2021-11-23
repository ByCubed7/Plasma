#pragma once

#include "TilemapRenderer.h"

#include "Shader.h"
#include "Font.h"
#include "Resources.h"

using namespace std;

TilemapRenderer::TilemapRenderer(Shader& shader)
{
    this->shader = shader;
}

TilemapRenderer::~TilemapRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void TilemapRenderer::DrawTilemap(glm::vec2 position, glm::vec2 size, float rotate, int frame, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f)); // translate
    //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    //model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
    //model = glm::scale(model, glm::vec3(size, 1.0f)); // scale
    this->shader.SetMatrix4("model", model);

    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    tilemap->tileSheet.Bind();


    glBindVertexArray(this->quadVAO);

    //glDrawArrays(GL_TRIANGLES, 0, tilemap->Count());
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
    //glDrawElements(GL_TRIANGLES, tilemap->Count() * 6, GL_UNSIGNED_INT, &(tilemap->tiles));
    glBindVertexArray(0);
}

void TilemapRenderer::Bind(Tilemap* tilemap)
{
    this->tilemap = tilemap;
    // IDEA

    initRenderData();
}

void TilemapRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}