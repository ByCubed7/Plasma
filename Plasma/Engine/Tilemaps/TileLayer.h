// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include "Tile.h"
#include "TileRender.h"

#include <map>
#include <vector>

#include <glm/glm.hpp>

namespace Tilemaps {
    class TileLayer
    {
    public:

        TileLayer();

        void SetTile(Tile tile);
        void DeleteTile(Tile tile);

        Tile GetTile(Vector2 position);
        bool IsTile(Vector2 position);
                
        /// <summary>
        /// Generates and Returns a TileLayers render data.
        /// </summary>
        /// <returns>Returns the TileLayers render data.</returns>
        TileRender GetRender();

        // - Attribute Gets


        size_t Count();
    private:
        std::map<Vector2, Tile> tiles;
    };
}