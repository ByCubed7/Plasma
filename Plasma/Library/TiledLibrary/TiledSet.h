#pragma once

#include <array>
#include <vector>
#include <unordered_map>

#include "TiledTile.h"

using namespace std;

namespace Tiled {
	class Set
	{
	public:
		// File Constructor
		Set(unordered_map<string, string> const& data,
			unordered_map<string, string> const& properties,
			vector<Tile> const& tiles);

		// - Gets

		string Name() const noexcept;
		string Source() const noexcept;
		string Property(string const& key) noexcept;

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

		array<unsigned int, 3> TransparentColour() const noexcept;

		Tile* GetTile(unsigned int tileID);

	private:
		string name;
		string source;

		unordered_map<string, string> properties;

		unsigned int firstGID, lastGID;
		unsigned int imageWidth, imageHeight;
		unsigned int tileWidth, tileHeight;
		unsigned int spacing;
		unsigned int margin;
		unsigned int offsetX, offsetY;
		unsigned int count;
		array<unsigned int, 3> transparentColour;
		vector<Tile> tiles;
	};
}
