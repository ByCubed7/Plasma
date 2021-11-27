// By @ByCubed7 on Twitter

#pragma once

#include "TilemapRenderer.h"

#include "Shader.h"
#include "Font.h"
#include "Resources.h"

TilemapRenderer::TilemapRenderer(Shader& shader)
{
    this->shader = shader;

    tileVAO = 0;
    verticesVBO = 0;
    instanceVBO = 0;
    tileIdInstanceVBO = 0;
    tilePositionInstanceVBO = 0;

    initRenderData();
}

TilemapRenderer::~TilemapRenderer()
{
    glDeleteVertexArrays(1, &tileVAO);
}

void TilemapRenderer::DrawTilemap(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, int frame, glm::vec3 color)
{
    /*
    cout << "[TilemapRenderer::DrawTilemap]" << endl;
    cout << " - of count: " << renderData.Count() << endl;
    cout << " - at position: " << renderData.tilePosition[0].first << ", " << renderData.tilePosition[0].second << endl;
    //cout << " - at position: " << renderData.tilePosition[1].first << ", " << renderData.tilePosition[1].second << endl;
    cout << endl;
    //*/

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
    shader.SetVector2f("spriteSize", { texture.Height, texture.Height });

    // Texture Frame
    //shader.SetInteger("index", frame);
    //*/
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();


    glBindVertexArray(tileVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tileIds.size());
    glBindVertexArray(0);
}

void TilemapRenderer::initRenderData()
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

    glGenVertexArrays(1, &tileVAO);
    
    glBindVertexArray(tileVAO);

    glGenBuffers(1, &verticesVBO);
    glGenBuffers(1, &tilePositionInstanceVBO);
    glGenBuffers(1, &tileIdInstanceVBO);

    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 0 : vec2 - Vertice position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // 1 : vec2 - Texture Coord
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TilemapRenderer::Update(Tilemap::RenderData tilemapRenderData)
{
    if (tilemapRenderData.Count() == 0) return;

    vector<float> tilemapRenderDataTileIds = tilemapRenderData.GetTileIds();

    if (tileIds != tilemapRenderDataTileIds) {
        tilePositions = tilemapRenderData.GetTilePositions();
        tileIds = tilemapRenderDataTileIds;
    }
    else return;

    //renderData = tilemapRenderData;

    cout << "[TilemapRenderer::Update] Start" << endl;

    glBindVertexArray(tileVAO);

    // 2 : vec2 - Tile Position
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, tilePositionInstanceVBO);
    glBufferData(GL_ARRAY_BUFFER, tilePositions.size() * sizeof(tilePositions), &tilePositions[0], GL_STATIC_DRAW);

    cout << "[TilemapRenderer::Update]" 
        << " Size: " << tilePositions.size()
        << " Mem: " << tilePositions.size() * sizeof(tilePositions)
        << " At: " << &tilePositions[0] << endl;

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(tilePositions[0]), (void*)0);
    glVertexAttribDivisor(2, 1);

    // 3 : float - Tile Id
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tileIdInstanceVBO);
    glBufferData(GL_ARRAY_BUFFER, tileIds.size() * sizeof(tileIds), &tileIds[0], GL_STATIC_DRAW);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(tileIds[0]), (void*)0);
    glVertexAttribDivisor(3, 1);

    // Clear the bound buffer
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for (int i = 0; i < tileIds.size(); ++i)
        cout << "Tile: " << tileIds[i]+1 << " at " << tilePositions[i].x << ", " << tilePositions[i].y << endl;
    

    //* Print any errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        cout << "[TilemapRenderer::Update] ERROR:" << err << endl;
    }//*/

    cout << "[TilemapRenderer::Update] End" << endl;
}