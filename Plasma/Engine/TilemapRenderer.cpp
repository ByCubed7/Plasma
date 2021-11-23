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

    glActiveTexture(GL_TEXTURE0);
    tilemap->tileSheet.Bind();

    glBindVertexArray(this->quadVAO);
    //glDrawArrays(GL_TRIANGLES, 0, tilemap->Count());
    glDrawElements(GL_TRIANGLES, tilemap->Count() * 6, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void TilemapRenderer::Bind(Tilemap* tilemap)
{
    this->tilemap = tilemap;
    initRenderData();
}

void TilemapRenderer::initRenderData()
{
    /* Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, tilemap->Count() * sizeof(unsigned char), &tilemap->tiles, GL_STATIC_DRAW);
    //*/

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int floatCount = get<0>(tilemap->TextureSize()) // for each tile
        * 4 // there are 4 vertices in each tile (since it's a square)
        * 2 // each vertex has two components: Position and Texcoord
        * 2; // each component has two fields: x and y

    vector<float> vertexData;
    vertexData.resize(floatCount);

    unsigned int i = 0;
    for (int x = 0; x < tilemap->width; x++)
    {
        for (int y = 0; y < tilemap->height; y++)
        {
            int tile = tilemap->tiles[{x, y}];
            float tx0 = (tile / 15) * get<0>(tilemap->tileSize);// +IRenderer.TileTexPadding;
            float ty0 = (tile % 15) * get<0>(tilemap->tileSize);// +IRenderer.TileTexPadding;
            float tySize = get<0>(tilemap->tileSize);// - IRenderer.TileTexPadding * 2;

            // vertex 0 (top left)
            vertexData[i + 0] = x; // position x
            vertexData[i + 1] = y; // position y
            vertexData[i + 2] = tx0; // texcoord x
            vertexData[i + 3] = ty0; // texcoord y
            i += 4;

            // vertex 1 (top right)
            vertexData[i + 0] = x + 1; // position x
            vertexData[i + 1] = y; // position y
            vertexData[i + 2] = tx0 + tySize; // texcoord x
            vertexData[i + 3] = ty0; // texcoord y
            i += 4;

            // vertex 2 (bottom left)
            vertexData[i + 0] = x; // position x
            vertexData[i + 1] = y + 1; // position y
            vertexData[i + 2] = tx0; // texcoord x
            vertexData[i + 3] = ty0 + tySize; // texcoord y
            i += 4;

            // vertex 3 (bottom right)
            vertexData[i + 0] = x + 1; // position x
            vertexData[i + 1] = y + 1; // position y
            vertexData[i + 2] = tx0 + tySize; // texcoord x
            vertexData[i + 3] = ty0 + tySize; // texcoord y
            i += 4;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData, GL_STATIC_DRAW);


    // Element Array Buffer

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, EBO);

    int indexCount = tilemap->Count() // for each tile
        * 6; // there are 6 vertices (two triangles, each with 3 vertices)
    vector<int> indices;
    indices.resize(indexCount);
    
    i = 0;
    unsigned int j = 0;
    for (int x = 0; x < tilemap->width; x++)
    {
        for (int y = 0; y < tilemap->height; y++)
        {
            indices[i + 0] = j;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 1;
            indices[i + 4] = j + 2;
            indices[i + 5] = j + 3;
            i += 6;
            j += 4;
            cout << i << " " << j << endl;
        }
    }
    cout << tilemap->width << " " << tilemap->height << endl;

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices, GL_STATIC_DRAW);

    // Vertex Array Object
    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

}