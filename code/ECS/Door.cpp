#include "Door.h"

Door::Door(Shader* _shader, glm::vec2 _init_position, float _width, float _heigth)
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
	m_model_id = glGetUniformLocation(m_shader->id, "model");
	m_base_color_id = glGetUniformLocation(m_shader->id, "base_color");
	//	Posicion de inicio donde va a empezar el enemigo
	//m_model = glm::translate(m_model, glm::vec3(_init_position.x, _init_position.y, 0.0f));
	m_position = _init_position;
	m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0.0f));
	m_rigidbody = new PhysicsComponent(m_position, _width, _heigth);
}

void Door::Draw(glm::vec2 _scroling)
{
	auto movement = -_scroling;
	m_position += movement;
	m_rigidbody->UpdatePosition(m_position);
	glBindVertexArray(VAO);
	glUniform4f(m_base_color_id, 0.4f, 0.5f, 1.f, 1.f);
	m_model = glm::translate(m_model, glm::vec3(movement.x, movement.y, 0));
	glUniformMatrix4fv(m_model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_shader->use();
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	m_shader->unuse();
}

glm::vec2 Door::GetPosition()
{
	return m_position;
}
