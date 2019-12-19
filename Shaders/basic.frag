#version 410

in vec3 Color;

uniform mat4 RotationMatrix;

out vec4 FragColor;

void main()
{
    FragColor = RotationMatrix * vec4(Color, 1.0);
}