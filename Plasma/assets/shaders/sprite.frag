#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform int offsetX;

uniform vec2 coords = vec2(1, 1);

void main()
{
    coords = vec2(TexCoords.x + offsetX, TexCoords.y);
    color = vec4(spriteColor, 1.0) * texture(image, coords);
}
