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

struct Renderer
{
	SpriteRenderer sprite;
	TextRenderer text;
	TilemapRenderer tilemap;

	Renderer(Shader& spriteShader, Shader& textShader, Shader& tilemapShader);
	~Renderer();
};

