// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "Tilemaps/Tilemap.h"
#include "Tilemaps/TileRender.h"

#include <vector>

namespace Render 
{
    class TilemapRenderer : Renderer
    {
    public:
        // Constructor (inits shaders/shapes)
        TilemapRenderer(Shader& shader);

        // Renders a defined quad textured with given sprite
        void DrawTileLayer(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(1.0f, 1.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));

        // Updates the tilemaps render data
        void Update(Tilemaps::TileRender render);

    private:

        void UpdateRender(Tilemaps::TileRender render);
        void UpdateRenderBuffer();

        // Rendering VBOs
        unsigned int verticesVBO, idInstanceVBO, positionInstanceVBO, rotscaInstanceVBO;
        unsigned int rotscaRow1InstanceVBO, rotscaRow2InstanceVBO, rotscaRow3InstanceVBO, rotscaRow4InstanceVBO;

        // Rendering States
        std::vector<float> tileIds;
        std::vector<glm::vec2> tilePositions;
        std::vector<glm::vec4> tileRotScasRow1, tileRotScasRow2, tileRotScasRow3, tileRotScasRow4;
    };
}
