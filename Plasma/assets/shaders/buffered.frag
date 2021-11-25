#version 330 core

in vec3 fColor;

out vec4 color;


void main()
{
    //color = vec4(fColor, 1.0);

    //color = vec4(fColor, 1.0);// * texture(image, uv);
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
