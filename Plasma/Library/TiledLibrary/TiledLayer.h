#pragma once

#include <vector>
#include <unordered_map>

namespace Tiled {
    class Layer
    {
    public:
        // Constructor
        Layer(
            const std::string& name,
            unsigned int width, unsigned int height,
            const std::unordered_map<std::string, std::string>& properties,
            const std::vector<std::vector<unsigned int>>& tiles
        );

        // - Gets
        unsigned Width() const noexcept;
        unsigned Height() const noexcept;
        std::string Name() const noexcept;
        std::string Property(std::string const& propertyName) noexcept;
        std::vector<std::vector<unsigned int>> Tiles() const noexcept;

    private:
        unsigned int width, height;
        std::string name;
        std::vector<std::vector<unsigned int>> tiles;
        std::unordered_map<std::string, std::string> properties;
    };
}
