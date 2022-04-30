// By @ByCubed7 on Twitter

#pragma once

#include "TileLayer.h"
#include "Tileset.h"

#include "../Resource.h"
#include "../Vector.h"
#include "../Render/Texture2D.h"

#include "TiledLibrary/TiledLoader.h"
#include <vector>

namespace Tilemaps {
    class Tilemap : Resource<Tilemap>
    {
    public:
        std::vector<TileLayer> layers;

        Texture2D tileSheet;
    
        Vector2 tileSize;
        Tileset tileset;

        Tilemap();

        void AddLayer();
        void AddLayer(TileLayer layer);

        // Lazy
        static inline Tiled::Loader tiled;
        static inline bool tiledLoaded = false;

    protected:
        Tilemap FromFile(const std::string filename) override;
        void Clear() override;
    };
}