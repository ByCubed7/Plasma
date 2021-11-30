// By @ByCubed7 on Twitter

#pragma once

#include "../Texture.h"
#include "TileLayer.h"
#include "Tile.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Tilemaps {
    class Tilemap
    {
    public:
        vector<TileLayer> layers;

        Texture2D tileSheet;

        //int width, height;
    
        pair<int, int> tileSize;

        Tilemap();

        void AddLayer(TileLayer layer);

        void AddTile(int layer, Tile tile);
        void AddTile(int layer, int id, glm::vec2 position);
        void AddTile(int layer, int id, glm::vec2 position, float rotation);
        void AddTile(int layer, int id, glm::vec2 position, float rotation, glm::vec2 scale);

        // - Attribute Gets

        int GetTileAt(int layer, glm::vec2 position);
        int GetTileAt(int layer, pair<int, int> position);
    };
}