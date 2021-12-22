// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include "Tile.h"
#include "TileRender.h"

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

        TileLayer();

        void AddTile(Tile tile);
        //void AddTile(int id, Vector2 position);
        //void AddTile(int id, Vector2 position, float rotation);
        //void AddTile(int id, Vector2 position, float rotation, Vector2 scale);
        
        TileRender GetRender();

        // - Attribute Gets

        int GetTileAt(Vector2 position);

        size_t Count();
    private:
        map<Vector2, Tile> tiles;
    };
}