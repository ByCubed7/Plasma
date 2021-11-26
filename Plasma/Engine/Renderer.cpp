// By @ByCubed7 on Twitter

#include "Renderer.h"

Renderer::Renderer(Shader& spriteShader, Shader& textShader, Shader& tilemapShader)
	: sprite(spriteShader), text(textShader), tilemap(textShader) {}

Renderer::~Renderer() {}