// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Tilemap.h"

#include <map>
#include <string>
#include <vector>


namespace Tilemaps {
	Tilemap::Tilemap() 
    {
        if (!tiledLoaded) {
            tiled = Tiled::Loader();
            tiledLoaded = true;
        }
    }

	void Tilemap::AddLayer(TileLayer layer)
	{
		layers.push_back(layer);
	}
    void Tilemap::AddLayer() { AddLayer(TileLayer()); }

	Tilemap Tilemap::FromFile(const std::string filename)
	{
        Tilemap map = Tilemap();

        // What happens when we can't find the file?
        // Invalid format? ect.
        tiled.LoadMap(filename, filename);

        Tiled::Map* tiledMap = tiled.GetMap(filename);

        // Convert the loaded map into a tilemap
        std::vector<Tiled::Layer> layers = tiledMap->Layers();

        for (int j = 0; j < layers.size(); j++)
        {
            auto tiles = layers[j].Tiles();

            map.AddLayer();


            for (int y = 0; y < tiledMap->Height(); ++y) {
                for (int x = 0; x < tiledMap->Width(); ++x) {
                    unsigned int id = tiles[y][x];

                    //cout << "First tile: " << tiles[0][0] << endl;
                    //if (j == 0) id = 3758096387;

                    // Read the flags
                    bool flipH = (id & Tiled::FLIPPED_HORIZONTALLY_FLAG);
                    bool flipV = (id & Tiled::FLIPPED_VERTICALLY_FLAG);
                    bool flipD = (id & Tiled::FLIPPED_DIAGONALLY_FLAG);

                    // Clear the flags
                    id &= ~(
                        Tiled::FLIPPED_HORIZONTALLY_FLAG |
                        Tiled::FLIPPED_VERTICALLY_FLAG |
                        Tiled::FLIPPED_DIAGONALLY_FLAG
                        );

                    // Converts the boolean mirror matrix to a rotation float and scale vector
                    // NOTE: This took me 5 hours and I found it by accedent at like 4am

                    Vector2Int scale = Vector2Int({
                       flipH ^ flipD ? -1 : 1,
                       flipV ? -1 : 1
                        });

                    if (flipD) {
                        int temp = scale.x;
                        scale.x = scale.y;
                        scale.y = temp;
                    }

                    int rotat = flipD ? 90 : 0;

                    // Add the tile
                    if (id != 0)
                    {
                        map.layers[j].SetTile(
                            Tilemaps::Tile(
                                map.tileset.GetIndexFromId(id),
                                { x, y },
                                rotat, scale
                            )
                        );

                    }
                }
            }
        }//*/

        /*
        for (int i = 0; i < layers.size(); i++ )
        {
            map.AddLayer();

            auto layer = layers[i];
            for (int y = 0; y < layer.Tiles().size(); y++)
            {
                auto row = layer.Tiles()[y];
                for (int x = 0; x < row.size(); x++)
                {
                    map.AddTile(i, row[x], glm::vec2(x, y));
                }
            }
        }*/

        return map;
	}

    void Tilemap::Clear()
    {
    }


}