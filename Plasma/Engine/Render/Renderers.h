// By @ByCubed7 on Twitter

#pragma once

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "TilemapRenderer.h"

class Shader;

namespace Render
{
	struct Renderers
	{
		SpriteRenderer sprite;
		TextRenderer text;
		TilemapRenderer tilemap;

		Renderers(Shader& spriteShader, Shader& textShader, Shader& tilemapShader);
		~Renderers();
	};
}
