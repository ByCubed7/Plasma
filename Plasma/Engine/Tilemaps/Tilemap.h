// By @ByCubed7 on Twitter

#pragma once

#include "../Texture.h"
#include "TileLayer.h"
#include "Tileset.h"
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
        Tileset tileset;

        Tilemap();

        void AddLayer();
        void AddLayer(TileLayer layer);

    private:
    };
}