#include "TiledMap.h"

namespace Tiled {
    void Map::Settings(vector<string> const& data, unordered_map<string, string> const& props) noexcept
    {
        version = stoi(data[0]);

        orientation = data[1];
        renderOrder = data[2];

        width = stoi(data[3]);
        height = stoi(data[4]);

        tileWidth = stoi(data[5]);
        tileHeight = stoi(data[6]);

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

    array<unsigned int, 3> Map::BackgroundColor() const noexcept { return backgroundColour; }

    string Map::Orientation() const noexcept { return orientation; }
    string Map::RenderOrder() const noexcept { return renderOrder; }

    void Map::AddTileset(Set const& newTileSet) noexcept { tiles.push_back(newTileSet); }

    Set* Map::GetTileset(string const& name) noexcept
    {
        for (size_t i = 0; i < tiles.size(); ++i)
            if (tiles[i].Name() == name)
                return &tiles[i];
        cout << "[Tiled] Tileset layer '" << name << "' could not be found." << endl;
        return nullptr;
    }

    void Map::AddLayer(Layer const& newLayer) noexcept { layers.push_back(newLayer); }

    Layer* Map::GetLayer(string const& name) noexcept
    {
        for (size_t i = 0; i < tiles.size(); ++i)
            if (layers[i].Name() == name)
                return &layers[i];
        cout << "[Tiled] Tile layer '" << name << "' could not be found." << endl;
        return nullptr;
    }

    vector<Layer>& Map::Layers() noexcept { return layers; }
}
