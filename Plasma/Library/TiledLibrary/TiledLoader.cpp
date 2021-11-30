#include "TiledLoader.h"

#include <iostream>

namespace Tiled {
	Loader::Loader() : maps() {}

	void Loader::LoadMap(string name, string path)
	{
		// String to hold file contents
		string fileContents = "";

		// Attempt to Load file using provided file path
		bool fileLoaded = LoadFile(path, fileContents);

		if (fileLoaded)
		{
			rapidxml::xml_document<char>* currentMap = new rapidxml::xml_document<char>;
			currentMap->parse<0>((char*)fileContents.c_str());

			rapidxml::xml_node<>* parentNode = currentMap->first_node("map");

			maps[name] = unique_ptr<Map>(new Map());

			LoadSettings(maps[name], parentNode);
			LoadTileSets(maps[name], parentNode);
			LoadLayers(maps[name], parentNode);

			delete currentMap;
			delete parentNode;
		}
		else
		{
			cout << "[Tiled] map '" << name << "' at '" << path << "' could not be Loaded." << endl;
		}
	}

	Map* Loader::GetMap(string name)
	{
		auto it = maps.find(name);
		if (it != maps.end())return it->second.get();

		cout << "[Tiled] map '" << name << "' not found." << endl;
		return nullptr;
	}

	void Loader::LoadSettings(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		vector<string> data;

		for (rapidxml::xml_attribute<char>* attr = parentNode->first_attribute(); attr; attr = attr->next_attribute())
			data.push_back(attr->value());


		string colourString = data[6];
		string colourSubstring = colourString.substr(1, colourString.length());

		unsigned int colour = stoi(colourSubstring, 0, 16);

		data.push_back(to_string(colour / 0x10000));
		data.push_back(to_string((colour / 0x100) % 0x100));
		data.push_back(to_string(colour / 0x10000));

		unordered_map<string, string> properties;

		LoadProperties(properties, parentNode);

		map->Settings(data, properties);
	}

	void Loader::LoadTileSets(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		rapidxml::xml_node<>* currentNode = parentNode;

		if (currentNode->first_node("tileset") != nullptr)
		{
			currentNode = currentNode->first_node("tileset");

			unordered_map<string, string> tileSetData;
			unordered_map<string, string> properties;
			vector<Tile> tiles;
			unordered_map<string, string> tileProperties;

			while (currentNode != nullptr)
			{
				for (rapidxml::xml_attribute<char>* attr = currentNode->first_attribute(); attr; attr = attr->next_attribute())
					tileSetData[attr->name()] = attr->value();


				rapidxml::xml_node<>* offsetNode = currentNode;
				if (offsetNode->first_node("tileoffset") != nullptr)
				{
					offsetNode = offsetNode->first_node("tileoffset");

					tileSetData["tileoffsetX"] = offsetNode->first_attribute()->value();
					tileSetData["tileoffsetY"] = offsetNode->first_attribute()->next_attribute()->value();
				}

				properties.clear();
				LoadProperties(properties, currentNode);

				currentNode = currentNode->first_node("image");
				for (rapidxml::xml_attribute<char>* attr = currentNode->first_attribute(); attr; attr = attr->next_attribute())
				{
					if (strcmp(attr->name(), "trans") == 0)
					{
						unsigned int colour = stoi(attr->value(), 0, 16);

						tileSetData["red"] = to_string(colour / 0x10000);
						tileSetData["green"] = to_string((colour / 0x100) % 0x100);
						tileSetData["blue"] = to_string(colour / 0x10000);
					}
					else
					{
						tileSetData[attr->name()] = attr->value();
					}
				}

				tiles.clear();
				rapidxml::xml_node<>* tileNode = currentNode->parent()->first_node("tile");
				while (tileNode != nullptr)
				{
					unsigned int tileID = atoi(tileNode->first_attribute()->value());
					LoadProperties(tileProperties, tileNode);
					tiles.push_back(Tile(tileID, tileProperties));

					tileProperties.clear();

					if (tileNode->next_sibling("tile") == nullptr) break;
					tileNode = tileNode->next_sibling("tile");
				}

				map->AddTileset(Set(tileSetData, properties, tiles));

				if (currentNode->parent()->next_sibling("tileset") == nullptr) break;

				tileSetData.clear();
				currentNode = currentNode->parent()->next_sibling("tileset");

			}
		}
	}

	void Loader::LoadLayers(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		rapidxml::xml_node<>* currentNode = parentNode;

		currentNode = currentNode->first_node("layer");

		vector<char*> layerVector;

		char* layerName = nullptr;
		unsigned int layerWidth = 0;
		unsigned int layerHeight = 0;
		unordered_map<string, string> layerProperties;

		while (currentNode != nullptr)
		{
			layerProperties.clear();
			layerVector.clear();

			for (rapidxml::xml_attribute<char>* attr = currentNode->first_attribute(); attr; attr = attr->next_attribute())
				layerVector.push_back(attr->value());

			layerName = layerVector[0];
			layerWidth = atoi(layerVector[1]);
			layerHeight = atoi(layerVector[2]);

			LoadProperties(layerProperties, currentNode);

			currentNode = currentNode->first_node("data");
			currentNode = currentNode->first_node("tile");

			vector<vector<unsigned int>> tiles(layerHeight, vector<unsigned int>(layerWidth));

			unsigned int currentTile = 0;
			unsigned int currentRow = 0;

			while (currentNode != nullptr)
			{
				if (currentTile < layerWidth)
				{
					tiles[currentRow][currentTile] = (unsigned int)stoul(currentNode->first_attribute()->value());

					currentTile++;

					if (currentNode->next_sibling("tile") == nullptr) break;
					currentNode = currentNode->next_sibling("tile");
				}
				else
				{
					currentTile = 0;
					currentRow++;
				}

			}

			map->AddLayer(Layer(layerName, layerWidth, layerHeight, layerProperties, tiles));

			currentNode = currentNode->parent()->parent()->next_sibling("layer");
		}
	}

	void Loader::LoadProperties(unordered_map<string, string>& properties, rapidxml::xml_node<>* parentNode)
	{
		rapidxml::xml_node<>* currentNode = parentNode;

		if (currentNode->first_node("properties") != nullptr)
		{
			currentNode = currentNode->first_node("properties");
			currentNode = currentNode->first_node("property");

			while (currentNode != nullptr)
			{
				properties[currentNode->first_attribute()->value()] = currentNode->first_attribute()->next_attribute()->value();
				currentNode = currentNode->next_sibling("property");
			}
		}
	}

	bool Loader::LoadFile(string path, string& fileContents)
	{
		ifstream file(path, ios::in | ios::binary);

		if (file)
		{
			file.seekg(0, ios::end);
			fileContents.resize((size_t)file.tellg());
			file.seekg(0, ios::beg);
			file.read(&fileContents[0], fileContents.size());
			file.close();

			return true;
		}
		return false;
	}
}
