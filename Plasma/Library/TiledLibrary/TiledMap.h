#pragma once

#include "TiledSet.h"
#include "TiledLayer.h"

#include <iostream>
#include <vector>
#include <unordered_map>

namespace Tiled {
    class Map
    {
    public:
        void Settings(std::vector<std::string> const& data, std::unordered_map<std::string, std::string> const& props) noexcept;

        // - Get

        int Version() const noexcept;
        unsigned int Width() const noexcept;
        unsigned int Height() const noexcept;
        unsigned int TileWidth() const noexcept;
        unsigned int TileHeight() const noexcept;
        std::array<unsigned int, 3> BackgroundColor() const noexcept;
        std::string Orientation() const noexcept;
        std::string RenderOrder() const noexcept;

        // TileSets
        void AddTileset(Set const& newTileSet) noexcept;
        Set* GetTileset(std::string const& tileSetName) noexcept;

        // Layers
        void AddLayer(Layer const& newLayer) noexcept;
        Layer* GetLayer(std::string const& layerName) noexcept;
        std::vector<Layer>& Layers() noexcept;

    private:
        int version;
        unsigned int width, height;
        unsigned int tileWidth, tileHeight;
        std::array<unsigned int, 3> backgroundColour;
        std::string orientation;
        std::string renderOrder;

        std::unordered_map<std::string, std::string> properties;

        std::vector<Layer> layers;
        std::vector<Set> tiles;
    };
}
