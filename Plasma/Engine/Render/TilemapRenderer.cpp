// By @ByCubed7 on Twitter


//#define VERBOSE

#pragma once

#include "TilemapRenderer.h"

#include "Renderer.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Font.h"
#include "../Resources.h"
#include "../Tilemaps/Tilemap.h"

namespace Render
{
    TilemapRenderer::TilemapRenderer(Shader& shader)
        : Renderer(shader)
    {
        float vertices[] = {
            // positions   // tex
            -0.5f,  0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.0f, 1.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  1.0f, 0.0f
        };

        glBindVertexArray(vertexArrayObject);

        glGenBuffers(1, &verticesVBO);
        glGenBuffers(1, &idInstanceVBO);
        glGenBuffers(1, &positionInstanceVBO);
        glGenBuffers(1, &rotscaInstanceVBO);
        glGenBuffers(1, &rotscaRow1InstanceVBO);
        glGenBuffers(1, &rotscaRow2InstanceVBO);
        glGenBuffers(1, &rotscaRow3InstanceVBO);
        glGenBuffers(1, &rotscaRow4InstanceVBO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);

        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);

        glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 0 : vec2 - Vertice position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        // 1 : vec2 - Texture Coord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void TilemapRenderer::DrawTileLayer(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, int frame, glm::vec3 color)
    {
        shader.Use();

        //* Prepare transformations
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f)); // translate
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
        model = glm::scale(model, glm::vec3(size, 1.0f)); // scale
        shader.SetMatrix4("model", model);


        // render textured quad
        shader.SetVector3f("spriteColor", color);

        // Set shadow render dims
        shader.SetVector2f("spriteSize", { texture.height, texture.height });

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(vertexArrayObject);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tileIds.size());
        glBindVertexArray(0);
    }

    void TilemapRenderer::Update(Tilemaps::TileRender render)
    {
        UpdateRender(render);
        UpdateRenderBuffer();
    }

    void TilemapRenderer::UpdateRender(Tilemaps::TileRender render)
    {
        if (render.Count() == 0) return;
        //if (tileIds == render.Ids()) return;

        tileIds = render.Ids();
        tilePositions = render.Positions();
        std::vector<glm::mat4> tileRotScas = render.RotScas();

        size_t len = tileIds.size();
        tileRotScasRow1.resize(len);
        tileRotScasRow2.resize(len);
        tileRotScasRow3.resize(len);
        tileRotScasRow4.resize(len);

        for (int i = 0; i < len; i++) {
            glm::mat4& mat4 = tileRotScas[i];
            tileRotScasRow1[i] = mat4[0];
            tileRotScasRow2[i] = mat4[1];
            tileRotScasRow3[i] = mat4[2];
            tileRotScasRow4[i] = mat4[3];
        }
    }

    void TilemapRenderer::UpdateRenderBuffer()
    {
        glBindVertexArray(vertexArrayObject);

        //* 2 : float - Tile Id
        glBindBuffer(GL_ARRAY_BUFFER, idInstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tileIds.size() * sizeof(tileIds[0]), tileIds.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);
        //*/

        //* 3 : vec2 - Tile Position
        glBindBuffer(GL_ARRAY_BUFFER, positionInstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tilePositions.size() * sizeof(tilePositions[0]), tilePositions.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
        //*/

        //* 4-8 : mat4 - Tile Rotation and Scale
        glBindBuffer(GL_ARRAY_BUFFER, rotscaRow1InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tileRotScasRow1.size() * sizeof(tileRotScasRow1[0]), tileRotScasRow1.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);

        glBindBuffer(GL_ARRAY_BUFFER, rotscaRow2InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tileRotScasRow2.size() * sizeof(tileRotScasRow2[0]), tileRotScasRow2.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);

        glBindBuffer(GL_ARRAY_BUFFER, rotscaRow3InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tileRotScasRow3.size() * sizeof(tileRotScasRow3[0]), tileRotScasRow3.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);

        glBindBuffer(GL_ARRAY_BUFFER, rotscaRow4InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, tileRotScasRow4.size() * sizeof(tileRotScasRow4[0]), tileRotScasRow4.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
        //*/

        // Clear the bound buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        /* Print any errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
            cout << "[TilemapRenderer::Update] ERROR:" << err << endl;
        //*/
    }
}