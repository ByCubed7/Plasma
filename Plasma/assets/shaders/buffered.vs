#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    fColor = aColor;
    gl_Position = projection * model * vec4(aPos + aOffset, 0.0, 1.0);
}
