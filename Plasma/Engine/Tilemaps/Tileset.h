// By @ByCubed7 on Twitter

#pragma once

#include <map>

namespace Tilemaps {
    class Tileset
    {
    public:
        //? Texture2D tileSheet;

        Tileset();

        void AddIndex(unsigned int id, unsigned int index);

        unsigned int GetIndexFromId(unsigned int id);
    
    private:
        std::map<unsigned int, unsigned int> idToIndex;
    };
}