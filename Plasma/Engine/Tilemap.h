// By @ByCubed7 on Twitter

#pragma once

#include "Texture.h"
#include "AABB.h"

#include <glm/vec2.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;

class Tilemap
{
public:
    struct RenderData
    {
        vector<int> tileId;
        vector<pair<int, int>> tilePosition;
        // Change pair to glm::vec2
        int Count() { return tileId.size(); }

        vector<float> GetTileIds()
        {
            vector<float> tileData;
            for (auto& tile : tileId)
                tileData.push_back(tile);
            return tileData;
        }

        vector<glm::vec2> GetTilePositions()
        {
            vector<glm::vec2> tileData;
            for (auto& tile : tilePosition)
                tileData.push_back(glm::vec2(tile.first, tile.second));
            return tileData;
        }
    };

    map<pair<int, int>, int> tiles;
    Texture2D tileSheet;

    int width, height;
    
    pair<int, int> tileSize;

    // Constructor (inits shaders/shapes)
    Tilemap();

    void AddTile(pair<int, int> position, int id);
    int Count();
    pair<int, int> TextureSize();

    RenderData GetRenderData();
};