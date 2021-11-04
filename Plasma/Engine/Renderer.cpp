#include "Renderer.h"

Renderer::Renderer(Shader& spriteShader, Shader& textShader) : sprite(spriteShader), text(textShader) {}

Renderer::~Renderer() {}

void Renderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f))
{
	this->sprite.DrawSprite(texture, position, size, rotate, frame, color);
}

void Renderer::RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot, glm::vec3 color)
{
	this->text.RenderText(text, x, y, scale, pivot, color);
}