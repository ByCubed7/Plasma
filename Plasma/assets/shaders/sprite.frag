#version 330 core

in vec2 TexCoords;

out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform vec2 size = vec2(64);
uniform vec2 crop = vec2(1);

void main()
{
    ivec2 totalTextureSize = textureSize(image, 0);

    float w = totalTextureSize.x;
    float h = totalTextureSize.y;

    // Normalize sprite size
    float dx = size.x / w;
    float dy = size.y / h;

    // Figure out number of tile cols of sprite sheet
    float cols = w / size.x;
    float rows = h / size.y;

    // From linear index to row/col pair
    float col = mod(crop.x, cols);
    float row = mod(crop.y, rows);

    // Finally to UV texture coordinates
    //vec2 uv = vec2(dx * TexCoords.x + col * dx, 1.0 - dy - row * dy + dy * TexCoords.y);
    vec2 uv = vec2(dx * TexCoords.x + col * dx, dy * TexCoords.y + row * dy);

    colour = vec4(spriteColor, 1.0) * texture(image, uv);
}
