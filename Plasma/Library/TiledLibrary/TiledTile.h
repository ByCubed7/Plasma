#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace Tiled {
    // A representation of a tile
    class Tile
    {
    public:
        // Constructor
        Tile(unsigned int id, unordered_map<string, string> const& properties);

        // - Gets

        unsigned int Id() const noexcept;
        string Property(string const& key) noexcept;

    private:
        // The tiles id
        unsigned int id;

        // User properties
        unordered_map<string, string> properties;
    };
}
