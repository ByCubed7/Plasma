// By @ByCubed7 on Twitter

#pragma once

#include "TileLayer.h"
#include "Tileset.h"

#include <vector>

namespace Tilemaps {
    class Tilemap
    {
    public:
        std::vector<TileLayer> layers;

        Texture2D tileSheet;
    
        Vector2 tileSize;
        Tileset tileset;

        Tilemap();

        void AddLayer();
        void AddLayer(TileLayer layer);
    };
}