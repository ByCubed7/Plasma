// By @ByCubed7 on Twitter

#pragma once

#include "Renderer.h"

#include <glm/glm.hpp>
#include <vector>

class Shader;
class Texture2D;
namespace Tilemaps { struct TileRender; }

namespace Render 
{
    class TilemapRenderer : public Renderer
    {
    public:
        // Constructor (inits shaders/shapes)
        TilemapRenderer(Shader& shader);

        // Renders a defined quad textured with given sprite
        void DrawTileLayer(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, int frame, glm::vec3 color);

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
