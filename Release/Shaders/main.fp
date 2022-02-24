#version 130

in vec4 Color;

out vec4 FragColor;

uniform vec4 mainColor;

void main()
{
	FragColor = mainColor;
}