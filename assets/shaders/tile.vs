#version 330 core

#define PI 3.14159265359

layout (location = 0) in vec2 verticePosition;
layout (location = 1) in vec2 texCoords;

layout (location = 2) in float tileId;

layout (location = 3) in vec2 tilePosition;

layout (location = 4) in vec4 tileRotScaR1;
layout (location = 5) in vec4 tileRotScaR2;
layout (location = 6) in vec4 tileRotScaR3;
layout (location = 7) in vec4 tileRotScaR4;


out vec2 TexCoords;
out float id;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = texCoords;
    id = tileId;

    mat4 tileRotationScale = mat4(tileRotScaR1, tileRotScaR2, tileRotScaR3, tileRotScaR4);

    gl_Position = projection * model * tileRotationScale * vec4(verticePosition + tilePosition, 0.0, 1.0);
}
