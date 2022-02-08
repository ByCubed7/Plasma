// By @ByCubed7 on Twitter

#include "Renderers.h"

namespace Render
{
	Renderers::Renderers(Shader& spriteShader, Shader& textShader, Shader& tilemapShader)
		: sprite(spriteShader), text(textShader), tilemap(tilemapShader) {}

	Renderers::~Renderers() 
	{
	}
}