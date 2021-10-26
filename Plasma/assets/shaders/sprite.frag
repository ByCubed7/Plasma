#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform ivec2 spriteSize = ivec2(1024);

uniform vec2 offset = vec2(0);

void main()
{
    ivec2 textureSize = textureSize(image, 0);
    
    // Here we assume the width and height have the same density
    ivec2 spriteDensity = textureSize / spriteSize;
    

    vec2 coords;
    coords = TexCoords / spriteDensity + offset;
    
    color = vec4(spriteColor, 1.0) * texture(image, coords);
}
