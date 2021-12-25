#include "TiledSet.h"

#include <iostream>

namespace Tiled {


	// Load in from file
	
	Set::Set(
		std::unordered_map<std::string, std::string> const& data,
		std::unordered_map<std::string, std::string> const& properties,
		std::vector<Tile> const& tiles)
	{
		name = data.at("name");
		source = data.at("source");

		this->properties = properties;
		this->tiles = tiles;

		firstGID = 0;
		lastGID = tiles.size();

		imageWidth = atoi(data.at("width").c_str());
		imageHeight = atoi(data.at("height").c_str());

		tileWidth = atoi(data.at("tilewidth").c_str());
		tileHeight = atoi(data.at("tileheight").c_str());

		offsetX = 0;
		offsetY = 0;

		spacing = 0;
		margin = 0;

		count = tiles.size();

		/*
		transparentColour = {
			(unsigned)atoi(data.at("red").c_str()),
			(unsigned)atoi(data.at("green").c_str()),
			(unsigned)atoi(data.at("blue").c_str())
		};
		*/
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

	std::array<unsigned int, 3> Set::TransparentColour() const noexcept { return transparentColour; }

	std::string Set::Name() const noexcept { return name; }
	std::string Set::Source() const noexcept { return source; }

	std::string Set::Property(std::string const &key) noexcept
	{
		auto prop = properties.find(key);
		if (prop != properties.end()) return prop->second;
		std::cout << "[Tiled] Property '" << key << "' not found." << std::endl;
		return nullptr;
	}

	Tile* Set::GetTile(unsigned int id)
	{
		for (unsigned int i = 0; i < lastGID; ++i)
			if (id == tiles[i].Id())
				return &tiles[id];
		std::cout << "[Tiled] Tile with ID '" << id << "' not found." << std::endl;
		return nullptr;
	}
}
