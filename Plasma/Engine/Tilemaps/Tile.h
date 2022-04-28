// By @ByCubed7 on Twitter

#pragma once

#include "../Vector.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Tilemaps {
    struct Tile
    {
        Tile();
        Tile(int id, Vector2Int position);
        Tile(int id, Vector2Int position, float rotation);
        Tile(int id, Vector2Int position, float rotation, Vector2Int scale);

        int id;
        Vector2Int position;
        float rotation;
        Vector2Int scale;
    };
}