#include "TiledLoader.h"

#include <iostream>

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// for string delimiter
static inline std::vector<std::string> split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}


namespace Tiled {
	Loader::Loader() : maps() {}

	void Loader::LoadMap(std::string name, std::string path)
	{
		// String to hold file contents
		std::string fileContents = "";

		// Attempt to Load file using provided file path
		bool fileLoaded = LoadFile(path, fileContents);

		if (fileLoaded)
		{
			rapidxml::xml_document<char>* currentMap = new rapidxml::xml_document<char>;
			currentMap->parse<0>((char*)fileContents.c_str());

			rapidxml::xml_node<>* parentNode = currentMap->first_node("map");

			maps[name] = std::unique_ptr<Map>(new Map());

			LoadSettings(maps[name], parentNode);
			LoadTileSets(maps[name], parentNode);
			LoadLayers(maps[name], parentNode);

			//delete currentMap;
			//delete parentNode;
		}
		else
		{
			std::cout << "[Tiled] map '" << name << "' at '" << path << "' could not be Loaded." << std::endl;
		}
	}

	Map* Loader::GetMap(std::string name)
	{
		auto it = maps.find(name);
		if (it != maps.end()) return it->second.get();

		std::cout << "[Tiled] map '" << name << "' not found." << std::endl;
		return nullptr;
	}

	void Loader::LoadSettings(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		std::vector<std::string> data;

		for (rapidxml::xml_attribute<char>* attr = parentNode->first_attribute(); attr; attr = attr->next_attribute())
			data.push_back(attr->value());


		std::string colourString = data[6];
		std::string colourSubstring = colourString.substr(1, colourString.length());

		unsigned int colour = std::stoi(colourSubstring, 0, 16);

		data.push_back(std::to_string(colour / 0x10000));
		data.push_back(std::to_string((colour / 0x100) % 0x100));
		data.push_back(std::to_string(colour / 0x10000));

		std::unordered_map<std::string, std::string> properties;
 

		LoadProperties(properties, parentNode);

		map->Settings(data, properties);
	}

	void Loader::LoadTileSets(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		return;
		// TODO: Load from seperate TSX file, rather than relying on TMX files
		//map->AddTileset(Set(tileSetData, properties, tiles));

	}

	void Loader::LoadLayers(std::unique_ptr<Map> const& map, rapidxml::xml_node<>* parentNode)
	{
		//return;

		rapidxml::xml_node<>* currentNode = parentNode->first_node("layer");

		while (currentNode) {


			// Get all of the properties of the layer element
			std::unordered_map<std::string, std::string> properties;
			for (const rapidxml::xml_attribute<>* a = currentNode->first_attribute(); a; a = a->next_attribute())
				properties[a->name()] = a->value();
			
			std::string name = properties.at((std::string)"name");
			unsigned int width = std::stoi(properties.at((std::string)"width"));
			unsigned int height = std::stoi(properties.at((std::string)"height"));

			// Load all of the tiles
			//cout << "Loading all of the tiles" << endl;
			std::vector<std::vector<unsigned int>> tiles(height, std::vector<unsigned int>(width));
			currentNode = currentNode->first_node("data");

			//cout << currentNode->value() << endl;

			// Grab the data, convert it to a list of ints
			//vector<unsigned int> data;

			std::string dataString = currentNode->value();
			std::string delimiter = ",";

			std::vector<std::string> data = split(dataString, delimiter);


			//for (auto i : data) cout << "::" << i << endl;

			//data.push_back((int)stoll(token));
			

			int index = 0;
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					tiles[y][x] = (unsigned int)stoul(data[index]);
					index++;
				}
			}

			currentNode = currentNode->parent();

			// Add on to the layers on to the map
			map->AddLayer(Layer(name.c_str(), width, height, properties, tiles));

			//if (currentNode != currentNode.last_node())

			currentNode = currentNode->next_sibling("layer");

		}

	}

	void Loader::LoadProperties(std::unordered_map<std::string, std::string>& properties, rapidxml::xml_node<>* parentNode)
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

	bool Loader::LoadFile(std::string path, std::string& fileContents)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);

		if (file)
		{
			file.seekg(0, std::ios::end);
			fileContents.resize((size_t)file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&fileContents[0], fileContents.size());
			file.close();

			return true;
		}
		return false;
	}
}
