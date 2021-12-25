#include "TiledTile.h"

#include <iostream>

namespace Tiled {
    Tile::Tile(unsigned int id, std::unordered_map<std::string, std::string> const& properties)
    {
        this->id = id;
        this->properties = properties;
    }

    unsigned Tile::Id() const noexcept { return id; }

    std::string Tile::Property(std::string const& key) noexcept
    {
        auto prop = properties.find(key);
        if (prop != properties.end())
            return prop->second;
        std::cout << "[Tiled] property '" << key << "' not found." << std::endl;
        return nullptr;
    }
}
