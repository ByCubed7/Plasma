// By @ByCubed7 on Twitter

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Tilemaps {
    struct Tile
    {
        Tile();
        Tile(int id, glm::vec2 position);
        Tile(int id, glm::vec2 position, float rotation);
        Tile(int id, glm::vec2 position, float rotation, glm::vec2 scale);

        int id;
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
}