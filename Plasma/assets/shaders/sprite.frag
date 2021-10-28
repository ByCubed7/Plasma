#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform ivec2 spriteSize = ivec2(1024);

uniform vec2 offset = vec2(1);

void main()
{
    ivec2 totalTextureSize = textureSize(image, 0); // (2048, 1024) 

    vec2 spriteDensity = totalTextureSize / spriteSize; // (2048, 1024) / (1024, 1024) = (2, 1)
    
    vec2 texOffset = vec2(0);
    if (offset.x != 0 || offset.y != 0) {
        texOffset = spriteDensity / offset; // (2, 1) / (0, 0)
    }
    
    color = vec4(spriteColor, 1.0) * texture(image, texOffset + TexCoords);
}
