// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "Tilemaps/Tilemap.h"
#include "Tilemaps/Render.h"

#include <vector>


class TilemapRenderer
{
public:
    // Constructor (inits shaders/shapes)
    TilemapRenderer(Shader& shader);

    // Destructor
    ~TilemapRenderer();

    // Renders a defined quad textured with given sprite
    void DrawTileLayer(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(1.0f, 1.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));

    // Updates the tilemaps render data
    void Update(Tilemaps::Render render);

private:
    // Render state
    Shader shader;
    unsigned int tileVAO;
    unsigned int verticesVBO, idInstanceVBO, positionInstanceVBO, rotscaInstanceVBO;
    unsigned int rotscaRow1InstanceVBO, rotscaRow2InstanceVBO, rotscaRow3InstanceVBO, rotscaRow4InstanceVBO;

    vector<float> tileIds;
    vector<glm::vec2> tilePositions;
    vector<glm::vec4> tileRotScasRow1, tileRotScasRow2, tileRotScasRow3, tileRotScasRow4;

    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

