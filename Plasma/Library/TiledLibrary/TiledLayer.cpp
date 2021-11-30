#include "TiledLayer.h"

#include <iostream>

namespace Tiled {
    Layer::Layer(
        const string& name,
        unsigned int width, unsigned int height,
        const unordered_map<string, string>& properties,
        const vector<vector<unsigned int>>& tiles)
    {
        this->name = name;
        this->width = width;
        this->height = height;
        this->properties = properties;
        this->tiles = tiles;
    }

    unsigned Layer::Width() const noexcept { return width; }
    unsigned Layer::Height() const noexcept { return height; }

    string Layer::Name() const noexcept { return name; }
    vector<vector<unsigned>> Layer::Tiles() const noexcept { return tiles; }

    string Layer::Property(string const& key) noexcept
    {
        auto prop = properties.find(key);
        if (prop != properties.end())
            return prop->second;
        cout << "[Tiled] Property '" << key << "' not found." << endl;
        return nullptr;
    }
}
