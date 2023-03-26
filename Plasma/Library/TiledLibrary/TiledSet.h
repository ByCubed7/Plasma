#pragma once

#include <array>
#include <vector>
#include <unordered_map>

#include "TiledTile.h"

namespace Tiled {
	class setTexture2D
	{
	public:
		// File Constructor
		setTexture2D(std::unordered_map<std::string, std::string> const& data,
			std::unordered_map<std::string, std::string> const& properties,
			std::vector<Tile> const& tiles);

		// - Gets

		std::string Name() const noexcept;
		std::string Source() const noexcept;
		std::string Property(std::string const& key) noexcept;

		unsigned int FirstGID() const noexcept;
		unsigned int LastGID() const noexcept;

		unsigned int ImageWidth() const noexcept;
		unsigned int ImageHeight() const noexcept;

		unsigned int TileWidth() const noexcept;
		unsigned int TileHeight() const noexcept;

		unsigned int Spacing() const noexcept;
		unsigned int Margin() const noexcept;
		unsigned int OffsetX() const noexcept;
		unsigned int OffsetY() const noexcept;

		unsigned int Count() const noexcept;

		std::array<unsigned int, 3> TransparentColour() const noexcept;

		Tile* GetTile(unsigned int tileID);

	private:
		std::string name;
		std::string source;

		std::unordered_map<std::string, std::string> properties;

		unsigned int firstGID, lastGID;
		unsigned int imageWidth, imageHeight;
		unsigned int tileWidth, tileHeight;
		unsigned int spacing;
		unsigned int margin;
		unsigned int offsetX, offsetY;
		unsigned int count;
		std::array<unsigned int, 3> transparentColour;
		std::vector<Tile> tiles;
	};
}
