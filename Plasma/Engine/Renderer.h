#pragma once

#include <iostream>

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Resources.h"

#include "../Library/glad.h"
#include <glm/glm.hpp>

using namespace std;

class Renderer
{
	SpriteRenderer sprite;
	TextRenderer text;

public:
	Renderer(Shader& spriteShader, Shader& textShader);
	~Renderer();

	void RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot = { 0.5f, 0.5f }, glm::vec3 color = glm::vec3(1.0f));
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));
};

