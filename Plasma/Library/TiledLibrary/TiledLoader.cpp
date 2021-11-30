#include "TiledLoader.h"

#include <iostream>

using namespace std;

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

			//delete currentMap;
			//delete parentNode;
		}
		else
		{
			cout << "[Tiled] map '" << name << "' at '" << path << "' could not be Loaded." << endl;
		}
	}

	Map* Loader::GetMap(string name)
	{
		auto it = maps.find(name);
		if (it != maps.end()) return it->second.get();

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
		return;
		// TODO: Load from seperate TSX file, rather than relying on TMX files
		//map->AddTileset(Set(tileSetData, properties, tiles));

	}

	void Loader::LoadLayers(unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		return;
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
