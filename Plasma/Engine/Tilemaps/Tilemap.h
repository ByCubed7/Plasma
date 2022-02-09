// By @ByCubed7 on Twitter

#pragma once

#include "TileLayer.h"
#include "Tileset.h"

#include "../Vector2.h"
#include "../Render/Texture2D.h"

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