#include "TiledLoader.h"

#include <iostream>

using namespace std;

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// for string delimiter
static inline vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}


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
		//return;

		rapidxml::xml_node<>* currentNode = parentNode->first_node("layer");

		while (currentNode) {


			// Get all of the properties of the layer element
			unordered_map<string, string> properties;
			for (const rapidxml::xml_attribute<>* a = currentNode->first_attribute(); a; a = a->next_attribute())
				properties[a->name()] = a->value();
			
			string name = properties.at((string)"name");
			unsigned int width = stoi(properties.at((string)"width"));
			unsigned int height = stoi(properties.at((string)"height"));

			// Load all of the tiles
			//cout << "Loading all of the tiles" << endl;
			vector<vector<unsigned int>> tiles(height, vector<unsigned int>(width));
			currentNode = currentNode->first_node("data");

			//cout << currentNode->value() << endl;

			// Grab the data, convert it to a list of ints
			//vector<unsigned int> data;

			string dataString = currentNode->value();
			string delimiter = ",";

			vector<string> data = split(dataString, delimiter);


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
