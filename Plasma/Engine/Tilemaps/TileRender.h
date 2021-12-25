// By @ByCubed7 on Twitter

#pragma once

#include "Tile.h"

#include <glm/glm.hpp>
#include <vector>

namespace Tilemaps {
    struct TileRender
    {
        std::vector<int> ids;
        std::vector<glm::vec2> positions;
        std::vector<glm::mat4> rotscas;

        void Add(Tile& tile);

        std::vector<float> Ids();
        std::vector<glm::vec2> Positions();
        std::vector<glm::mat4> RotScas();

        size_t Count();
    };
}