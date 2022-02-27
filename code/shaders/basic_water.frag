#version 330 core

in vec4 Base_Color;
out vec4 Color;

void main()
{
	vec4 out_color = Base_Color;
	Color = out_color;
}