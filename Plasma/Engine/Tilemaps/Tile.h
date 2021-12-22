// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Tilemaps {
    struct Tile
    {
        Tile();
        Tile(int id, Vector2 position);
        Tile(int id, Vector2 position, float rotation);
        Tile(int id, Vector2 position, float rotation, Vector2 scale);

        int id;
        Vector2 position;
        float rotation;
        Vector2 scale;
    };
}