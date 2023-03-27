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

        void add(const Tile& tile);

        const size_t& size() const;
    };
}