#pragma once

#include <string>
#include <unordered_map>

namespace Tiled {
    // A representation of a tile
    class Tile
    {
    public:
        // Constructor
        Tile(unsigned int id, std::unordered_map<std::string, std::string> const& properties);

        // - Gets

        unsigned int Id() const noexcept;
        std::string Property(std::string const& key) noexcept;

    private:
        // The tiles id
        unsigned int id;

        // User properties
        std::unordered_map<std::string, std::string> properties;
    };
}
