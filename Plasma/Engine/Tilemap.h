// By @ByCubed7 on Twitter

#pragma once

#include "Texture.h"
#include "AABB.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;


class Tilemap
{
public:

    struct Tile
    {
        Tile();
        Tile(int id, glm::vec2 position);
        Tile(int id, glm::vec2 position, float rotation);
        Tile(int id, glm::vec2 position, float rotation, glm::vec2 scale);

        int id;
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };

    struct Render
    {
        vector<int> ids;
        vector<glm::vec2> positions;
        vector<glm::mat4> rotscas;

        void Add(Tile tile);

        vector<float> Ids();
        vector<glm::vec2> Positions();
        vector<glm::mat4> RotScas();

        int Count();
    };

    vector<Tile> tiles;
    Texture2D tileSheet;

    //int width, height;
    
    pair<int, int> tileSize;

    Tilemap();

    void AddTile(Tile tile);
    void AddTile(int id, glm::vec2 position);
    void AddTile(int id, glm::vec2 position, float rotation);
    void AddTile(int id, glm::vec2 position, float rotation, glm::vec2 scale);
    Render GetRender();

    // - Attribute Gets

    int GetTileAt(glm::vec2 position);
    int GetTileAt(pair<int, int> position);

    int Count();
    pair<int, int> TextureSize();
};