#include "Renderer.h"

Renderer::Renderer(Shader& spriteShader, Shader& textShader) : sprite(spriteShader), text(textShader) {}

Renderer::~Renderer() {}

void Renderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, int frame, glm::vec3 color)
{
	this->sprite.DrawSprite(texture, position, size, rotate, frame, color);
}

void Renderer::RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot, glm::vec3 color)
{
	this->text.RenderText(text, x, y, scale, pivot, color);
}