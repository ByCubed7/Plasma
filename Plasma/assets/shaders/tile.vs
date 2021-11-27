#version 330 core

layout (location = 0) in vec2 verticePosition;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec2 tilePosition;

layout (location = 3) in float tileId;


out vec2 TexCoords;
out float id;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = texCoords;
    id = tileId;
    gl_Position = projection * model * vec4(verticePosition + tilePosition, 0.0, 1.0);
}
