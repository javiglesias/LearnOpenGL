#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform vec4 base_color;

out vec4 Base_Color;

void main()
{
	gl_Position = model * vec4(aPos, 1.0);
	Base_Color = base_color;
}