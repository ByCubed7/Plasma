// By @ByCubed7 on Twitter

#pragma once

#include "Tile.h"

#include "../../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Tilemaps {
    struct TileRender
    {
        vector<int> ids;
        vector<glm::vec2> positions;
        vector<glm::mat4> rotscas;

        void Add(Tile& tile);

        vector<float> Ids();
        vector<glm::vec2> Positions();
        vector<glm::mat4> RotScas();

        size_t Count();
    };
}