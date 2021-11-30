#pragma once

#include "TiledSet.h"
#include "TiledLayer.h"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

namespace Tiled {
    class Map
    {
    public:
        void Settings(vector<string> const& data, unordered_map<string, string> const& props) noexcept;

        // - Get

        int Version() const noexcept;
        unsigned int Width() const noexcept;
        unsigned int Height() const noexcept;
        unsigned int TileWidth() const noexcept;
        unsigned int TileHeight() const noexcept;
        array<unsigned int, 3> BackgroundColor() const noexcept;
        string Orientation() const noexcept;
        string RenderOrder() const noexcept;

        // TileSets
        void AddTileset(Set const& newTileSet) noexcept;
        Set* GetTileset(string const& tileSetName) noexcept;

        // Layers
        void AddLayer(Layer const& newLayer) noexcept;
        Layer* GetLayer(string const& layerName) noexcept;
        vector<Layer>& Layers() noexcept;

    private:
        int version;
        unsigned int width, height;
        unsigned int tileWidth, tileHeight;
        array<unsigned int, 3> backgroundColour;
        string orientation;
        string renderOrder;

        unordered_map<string, string> properties;

        vector<Layer> layers;
        vector<Set> tiles;
    };
}
