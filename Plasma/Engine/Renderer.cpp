#include "Renderer.h"

Renderer::Renderer(Shader& spriteShader, Shader& textShader) : sprite(spriteShader), text(textShader) {}

Renderer::~Renderer() {}