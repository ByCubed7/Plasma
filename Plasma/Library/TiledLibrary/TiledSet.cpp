

#include "TiledSet.h"

#include <iostream>

namespace Tiled {


	// Load in from file
	
	setTexture2D::setTexture2D(
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

	unsigned int setTexture2D::FirstGID() const noexcept { return firstGID; }
	unsigned int setTexture2D::LastGID() const noexcept { return lastGID; }

	unsigned int setTexture2D::ImageWidth() const noexcept { return imageWidth; }
	unsigned int setTexture2D::ImageHeight() const noexcept { return imageHeight; }

	unsigned int setTexture2D::TileWidth() const noexcept { return tileWidth; }
	unsigned int setTexture2D::TileHeight() const noexcept { return tileHeight; }

	unsigned int setTexture2D::Spacing() const noexcept { return spacing; }
	unsigned int setTexture2D::Margin() const noexcept { return margin; }

	unsigned int setTexture2D::OffsetX() const noexcept { return offsetX; }
	unsigned int setTexture2D::OffsetY() const noexcept { return offsetY; }

	unsigned int setTexture2D::Count() const noexcept { return count; }

	std::array<unsigned int, 3> setTexture2D::TransparentColour() const noexcept { return transparentColour; }

	std::string setTexture2D::Name() const noexcept { return name; }
	std::string setTexture2D::Source() const noexcept { return source; }

	std::string setTexture2D::Property(std::string const &key) noexcept
	{
		auto prop = properties.find(key);
		if (prop != properties.end()) return prop->second;
		std::cout << "[Tiled] Property '" << key << "' not found." << std::endl;
		return nullptr;
	}

	Tile* setTexture2D::GetTile(unsigned int id)
	{
		for (unsigned int i = 0; i < lastGID; ++i)
			if (id == tiles[i].Id())
				return &tiles[id];
		std::cout << "[Tiled] Tile with ID '" << id << "' not found." << std::endl;
		return nullptr;
	}
}
