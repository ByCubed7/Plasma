#pragma once

#include "Texture.h"
#include "AABB.h"

#include <map>
#include <string>
#include <vector>

using namespace std;


class Tilemap
{
public:

    map<tuple<int, int>, int> tiles;
    Texture2D tileSheet;

    int width, height;
    
    tuple<int, int> tileSize;

    // Constructor (inits shaders/shapes)
    Tilemap();

    void AddTile(tuple<int, int> position, int id);
    int Count();
    tuple<int, int> TextureSize();

    void Bind();
};
