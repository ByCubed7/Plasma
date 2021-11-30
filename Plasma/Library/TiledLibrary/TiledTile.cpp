#include "TiledTile.h"

#include <iostream>

namespace Tiled {
    Tile::Tile(unsigned int id, unordered_map<string, string> const& properties)
    {
        this->id = id;
        this->properties = properties;
    }

    unsigned Tile::Id() const noexcept { return id; }

    string Tile::Property(string const& key) noexcept
    {
        auto prop = properties.find(key);
        if (prop != properties.end())
            return prop->second;
        cout << "[Tiled] property '" << key << "' not found." << endl;
        return nullptr;
    }
}
