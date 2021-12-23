// By @ByCubed7 on Twitter

#pragma once

#include "../Vector2.h"

#include "Tile.h"
#include "TileRender.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

namespace Tilemaps {
    class TileLayer
    {
    public:

        TileLayer();

        void SetTile(Tile tile);
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
        map<Vector2, Tile> tiles;
    };
}