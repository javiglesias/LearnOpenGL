#include "Grass.h"


Grass::Grass(glm::vec2 _position, float _width, float _height, Shader* _shader, Color _color)
{
	m_position = _position;
	m_shape_size = Shape_Size(_width, _height);
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
	//	Posicion de inicio donde va a empezar el enemigo
	m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0));
	m_shader_base_color = _color;
	m_position.x = m_position.x - 0.075f;
	m_position.y = m_position.y - 0.05f;
}

PhysicsComponent* Grass::GetPhysicsComponent()
{
	return m_rigidbody;
}

void Grass::Draw()
{
	glBindVertexArray(VAO);
	SetShaderColor(m_shader_base_color);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_shader->unuse();
}
void Grass::Move(glm::vec2 _scrolling)
{
	m_movement -= _scrolling;
	m_position -= _scrolling;
	m_model = glm::translate(m_model, glm::vec3(m_movement.x, m_movement.y, 0));
	m_movement = glm::vec2(0.f);
}


void Grass::UpdateGraphics(Color _color)
{
	m_shader_base_color = _color;
	SetShaderColor(m_shader_base_color);
}

void Grass::UpdatePhysics()
{
	m_rigidbody->UpdatePhysics();
}

bool Grass::UpdatePhysics(Entity* _target)
{
	return false;
}

glm::vec2 Grass::GetPosition()
{
	return m_position;
}

void Grass::UpdateIA()
{
	/*float increment = 0.0001f;
	if (m_position.x >= .9f)
	{
		increment = -sin(rand() % 2 / 10.f);
	}
	else if (m_position.x <= -.9f)
	{
		increment = sin(rand() % 2 / 10.f);
	}
	m_movement.x += increment;*/
}

void Grass::SetShaderColor(Color _color)
{
	glUniform4f(base_color_id, _color.r, _color.g, _color.b, _color.a);
}