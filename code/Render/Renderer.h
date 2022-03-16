#pragma once
#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Renderer
{
public:
	
private:
	unsigned int VBO = -1;
	unsigned int VAO = -1;
	unsigned int base_color_id = -1;
	unsigned int model_id = -1;
	float m_shape[18];
	glm::mat4 m_model{ 1.0f };
	Shader* m_shader;
	glm::vec2 m_position{ 0.f };
};

