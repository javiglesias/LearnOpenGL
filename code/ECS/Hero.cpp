#include "Hero.h"

Hero::Hero(Shader* _shader, glm::vec2 _init_position)
{
	shader = _shader;
	m_rigidbody = new PhysicsComponent(m_position, m_width, m_height);
	m_ears = new SoundComponent();
	m_ears->PlaySFX(m_ears->WALK);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	model_id = glGetUniformLocation(shader->id, "model");
	base_color_id = glGetUniformLocation(shader->id, "base_color");
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape), shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	m_position = _init_position;
	m_center.x = m_position.x;
	m_center.y = m_position.y - 0.025f;
	m_rigidbody = new PhysicsComponent(m_position, 0.02f, 0.05f);
}

void Hero::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 1,0,0,1);
	m_model = glm::translate(m_model, glm::vec3(m_translate.x, m_translate.y, 0.0f));
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_translate = glm::vec2(0.0f);
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
}

void Hero::Move(glm::vec2 _movement)
{
	if (m_center.x + _movement.x < -1 ||
		m_center.x + _movement.x > 1	||
		m_center.y + _movement.y < -1 ||
		m_center.y + _movement.y > 1)
	{
		return;
	}
	m_position += _movement;
	m_translate = _movement;
	m_center.x = m_position.x;
	m_center.y = m_position.y - 0.025f;
	m_rigidbody->UpdatePosition(m_center);
}

void Hero::UpdatePhysics()
{
	m_rigidbody->UpdatePhysics();
}

void Hero::UpdateSounds()
{
	
}

glm::vec2 Hero::GetPosition()
{
	return m_position;
}

glm::vec2 Hero::GetNextPosition()
{
	return m_next_position;
}

Entity::Shape_Size Hero::GetSize()
{
	return Shape_Size(0.f, 0.f);
}

void Hero::SetNextPosition(glm::vec2 _next_position)
{
	m_next_position += _next_position;
}
