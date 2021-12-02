// By @ByCubed7 on Twitter

#pragma once

#include <iostream>

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "TilemapRenderer.h"
#include "Resources.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>

using namespace std;

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
