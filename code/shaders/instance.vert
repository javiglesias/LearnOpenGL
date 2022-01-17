#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform vec4 base_color;

out vec4 Base_Color;

void main()
{
	
	vec3 pos_instance;
	float normalized_id = gl_InstanceID * 0.05;
	pos_instance = vec3(aPos.x + normalized_id, aPos.y , aPos.z);
	gl_Position = model * vec4(pos_instance, 1.0);
	Base_Color = base_color;
}