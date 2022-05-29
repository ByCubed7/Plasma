

#include "TiledMap.h"

namespace Tiled {
    void Map::Settings(std::vector<std::string> const& data, std::unordered_map<std::string, std::string> const& props) noexcept
    {
        version = stoi(data[1]);

        orientation = data[2];
        renderOrder = data[3];

        width = stoi(data[4]);
        height = stoi(data[5]);

        tileWidth = stoi(data[6]);
        tileHeight = stoi(data[7]);

        backgroundColour[0] = stoi(data[8]);
        backgroundColour[1] = stoi(data[8]);
        backgroundColour[2] = stoi(data[8]);

        properties = props;
    }

    int Map::Version() const noexcept { return version; }

    unsigned int Map::Width() const noexcept { return width; }
    unsigned int Map::Height() const noexcept { return height; }
    unsigned int Map::TileWidth() const noexcept { return tileWidth; }
    unsigned int Map::TileHeight() const noexcept { return tileHeight; }

    std::array<unsigned int, 3> Map::BackgroundColor() const noexcept { return backgroundColour; }

    std::string Map::Orientation() const noexcept { return orientation; }
    std::string Map::RenderOrder() const noexcept { return renderOrder; }

    void Map::AddTileset(Set const& newTileSet) noexcept { tiles.push_back(newTileSet); }

    Set* Map::GetTileset(std::string const& name) noexcept
    {
        for (size_t i = 0; i < tiles.size(); ++i)
            if (tiles[i].Name() == name)
                return &tiles[i];
        std::cout << "[Tiled] Tileset layer '" << name << "' could not be found." << std::endl;
        return nullptr;
    }

    void Map::AddLayer(Layer const& newLayer) noexcept { layers.push_back(newLayer); }

    Layer* Map::GetLayer(std::string const& name) noexcept
    {
        for (size_t i = 0; i < tiles.size(); ++i)
            if (layers[i].Name() == name)
                return &layers[i];
        std::cout << "[Tiled] Tile layer '" << name << "' could not be found." << std::endl;
        return nullptr;
    }

    std::vector<Layer>& Map::Layers() noexcept { return layers; }
}
