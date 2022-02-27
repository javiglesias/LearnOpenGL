#include "Corridor.h"

Corridor::Corridor(glm::vec2 _init_position, Shader* _shader, Color _color)
{
	m_shader = _shader;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_shape), m_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	model_id = glGetUniformLocation(m_shader->id, "model");
	base_color_id = glGetUniformLocation(m_shader->id, "base_color");
	alive_id = glGetUniformLocation(m_shader->id, "is_alive");
	//	Posicion de inicio donde va a empezar el enemigo
	m_model = glm::translate(m_model, glm::vec3(_init_position.x, _init_position.y, 0.0f));
	m_position = _init_position;
	m_shape_size = new Shape_Size(0.1f, 0.1f);
	m_shader_base_color = _color;
}

void Corridor::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, m_shader_base_color.r, m_shader_base_color.g, 
		m_shader_base_color.b, m_shader_base_color.a);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_shader->unuse();
}

void Corridor::Move(glm::vec2 _scrolling)
{
	m_position -= _scrolling;
	m_model = glm::translate(m_model, glm::vec3(-_scrolling.x, -_scrolling.y, 0.0f));
}
