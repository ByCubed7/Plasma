#include "Renderer.h"

Renderer::Renderer(Shader& spriteShader, Shader& textShader) : sprite(spriteShader), text(textShader)
{}

Renderer::~Renderer() {}

void Renderer::LoadFont(string font, unsigned int fontSize) {}

void Renderer::RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot, glm::vec3 color)
{
	
}