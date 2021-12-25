#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <memory>

#include "RapidXML/rapidxml.hpp"

#include "TiledMap.h"
#include "TiledLayer.h"
#include "TiledSet.h"
#include "TiledTile.h"

namespace Tiled {

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    class Loader
    {
    public:
        Loader();

        void LoadMap(std::string mapName, std::string filePath);
        Map* GetMap(std::string mapName);

    private:
        void LoadSettings(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadTileSets(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadLayers(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadProperties(std::unordered_map<std::string, std::string>& propertiesMap, rapidxml::xml_node<>* parentNode);

        // File loading
        bool LoadFile(std::string filePath, std::string& fileContents);

        // Loaded Maps cache
        std::unordered_map<std::string, std::unique_ptr<Map>> maps;
    };
}
