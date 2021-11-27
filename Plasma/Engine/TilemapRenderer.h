// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "Tilemap.h"

#include <vector>


class TilemapRenderer
{
public:
    // Constructor (inits shaders/shapes)
    TilemapRenderer(Shader& shader);

    // Destructor
    ~TilemapRenderer();

    // Renders a defined quad textured with given sprite
    void DrawTilemap(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));

    // Updates the tilemaps render data
    void Update(Tilemap::RenderData tilemapRenderData);

private:
    // Render state
    Shader shader;
    unsigned int tileVAO, verticesVBO, instanceVBO, tileIdInstanceVBO, tilePositionInstanceVBO;

    vector<glm::vec2> tilePositions;
    vector<float> tileIds;

    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

