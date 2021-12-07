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

using namespace std;

namespace Tiled {

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    class Loader
    {
    public:
        Loader();

        void LoadMap(string mapName, string filePath);
        Map* GetMap(string mapName);

    private:
        void LoadSettings(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadTileSets(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadLayers(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode);
        void LoadProperties(unordered_map<string, string>& propertiesMap, rapidxml::xml_node<>* parentNode);

        // File loading
        bool LoadFile(string filePath, string& fileContents);

        // Loaded Maps cache
        unordered_map<string, unique_ptr<Map>> maps;
    };
}