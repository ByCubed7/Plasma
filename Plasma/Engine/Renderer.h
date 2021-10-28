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

	// Loading

	void LoadFont(string font, unsigned int fontSize);

	// Rendering

	void RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot = { 0.5f, 0.5f }, glm::vec3 color = glm::vec3(1.0f));

};

