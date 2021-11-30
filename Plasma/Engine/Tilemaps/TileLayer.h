// By @ByCubed7 on Twitter

#pragma once

#include "Tile.h"
#include "Render.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Tilemaps {
    class TileLayer
    {
    public:
        vector<Tile> tiles;

        TileLayer();

        void AddTile(Tile tile);
        void AddTile(int id, glm::vec2 position);
        void AddTile(int id, glm::vec2 position, float rotation);
        void AddTile(int id, glm::vec2 position, float rotation, glm::vec2 scale);
        
        Render GetRender();

        // - Attribute Gets

        int GetTileAt(glm::vec2 position);
        int GetTileAt(pair<int, int> position);

        int Count();
    };
}