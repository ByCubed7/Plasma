#version 330 core

in vec2 TexCoords;
in float id;

out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform vec2 spriteSize = vec2(1024);
//uniform int index;

void main()
{
    ivec2 totalTextureSize = textureSize(image, 0);

    float w = totalTextureSize.x;
    float h = totalTextureSize.y;

    // Normalize sprite size
    float dx = spriteSize.x / w;
    float dy = spriteSize.y / h;

    // Figure out number of tile cols of sprite sheet
    float cols = w / spriteSize.x;

    // From linear index to row/col pair
    float col = mod(id, cols);
    float row = floor(id / cols);

    // Finally to UV texture coordinates
    vec2 uv = vec2(dx * TexCoords.x + col * dx, 1.0 - dy - row * dy + dy * TexCoords.y);

    colour = vec4(spriteColor, 1.0) * texture(image, uv);
    //colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
