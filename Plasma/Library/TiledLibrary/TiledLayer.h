#pragma once

#include <vector>
#include <unordered_map>

using namespace std;

namespace Tiled {
    class Layer
    {
    public:
        // Constructor
        Layer(
            string const& name,
            unsigned width, unsigned height,
            unordered_map<string, string> const& properties,
            vector<vector<unsigned>> const& tiles
        );

        // - Gets
        unsigned Width() const noexcept;
        unsigned Height() const noexcept;
        string Name() const noexcept;
        string Property(string const& propertyName) noexcept;
        vector<vector<unsigned int>> Tiles() const noexcept;

    private:
        unsigned int width, height;
        string name;
        vector<vector<unsigned int>> tiles;
        unordered_map<string, string> properties;
    };
}
