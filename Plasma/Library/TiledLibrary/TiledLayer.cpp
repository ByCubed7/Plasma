// By @ByCubed7 on Twitter


//#define VERBOSE

#include "TiledLayer.h"

#include <iostream>

namespace Tiled {
    Layer::Layer(
        const std::string& name,
        unsigned int width, unsigned int height,
        const std::unordered_map<std::string, std::string>& properties,
        const std::vector<std::vector<unsigned int>>& tiles)
    {
        this->name = name;
        this->width = width;
        this->height = height;
        this->properties = properties;
        this->tiles = tiles;
    }

    unsigned Layer::Width() const noexcept { return width; }
    unsigned Layer::Height() const noexcept { return height; }

    std::string Layer::Name() const noexcept { return name; }
    std::vector<std::vector<unsigned>> Layer::Tiles() const noexcept { return tiles; }

    std::string Layer::Property(std::string const& key) noexcept
    {
        auto prop = properties.find(key);
        if (prop != properties.end())
            return prop->second;
        std::cout << "[Tiled] Property '" << key << "' not found." << std::endl;
        return nullptr;
    }
}
