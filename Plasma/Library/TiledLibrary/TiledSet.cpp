#include "TiledSet.h"

#include <iostream>

namespace Tiled {


	// Load in from file
	
	Set::Set(
		unordered_map<string, string> const& data,
		unordered_map<string, string> const& properties,
		vector<Tile> const& tiles)
	{
		name = data.at("name");
		source = data.at("source");

		this->properties = properties;
		this->tiles = tiles;

		firstGID = atoi(data.at("firstgid").c_str());
		lastGID = tiles.back().Id();

		imageWidth = atoi(data.at("width").c_str());
		imageHeight = atoi(data.at("height").c_str());

		tileWidth = atoi(data.at("tilewidth").c_str());
		tileHeight = atoi(data.at("tileheight").c_str());

		offsetX = atoi(data.at("tileoffsetX").c_str());
		offsetY = atoi(data.at("tileoffsetY").c_str());

		spacing = atoi(data.at("spacing").c_str());
		margin = atoi(data.at("margin").c_str());

		count = atoi(data.at("tilecount").c_str());

		transparentColour = {
			(unsigned)atoi(data.at("red").c_str()),
			(unsigned)atoi(data.at("green").c_str()),
			(unsigned)atoi(data.at("blue").c_str())
		};

	}

	unsigned int Set::FirstGID() const noexcept { return firstGID; }
	unsigned int Set::LastGID() const noexcept { return lastGID; }

	unsigned int Set::ImageWidth() const noexcept { return imageWidth; }
	unsigned int Set::ImageHeight() const noexcept { return imageHeight; }

	unsigned int Set::TileWidth() const noexcept { return tileWidth; }
	unsigned int Set::TileHeight() const noexcept { return tileHeight; }

	unsigned int Set::Spacing() const noexcept { return spacing; }
	unsigned int Set::Margin() const noexcept { return margin; }

	unsigned int Set::OffsetX() const noexcept { return offsetX; }
	unsigned int Set::OffsetY() const noexcept { return offsetY; }

	unsigned int Set::Count() const noexcept { return count; }

	array<unsigned int, 3> Set::TransparentColour() const noexcept { return transparentColour; }

	string Set::Name() const noexcept { return name; }
	string Set::Source() const noexcept { return source; }

	string Set::Property(string const &key) noexcept
	{
		auto prop = properties.find(key);
		if (prop != properties.end()) return prop->second;
		cout << "[Tiled] Property '" << key << "' not found." << endl;
		return nullptr;
	}

	Tile* Set::GetTile(unsigned int id)
	{
		for (unsigned int i = 0; i < lastGID; ++i)
			if (id == tiles[i].Id())
				return &tiles[id];
		cout << "[Tiled] Tile with ID '" << id << "' not found." << endl;
		return nullptr;
	}
}
