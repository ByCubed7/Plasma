// By @ByCubed7 on Twitter

#pragma once

#include <iostream>

#include "Shader.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

#include "../Engine/Component.h"
#include "../Engine/Event.h"
#include "../Engine/Dispatcher.h"

#include "../Tilemaps/TilemapRenderer.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>

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
