#include "Hero.h"

Hero::Hero(glm::vec2 _init_position, float _width, float _height)
{
	m_shape_size = Shape_Size(_width, _height);
	//	Width
	shape[3] = -_width;
	shape[6] = _width;
	//	Height
	shape[4] = -_height;
	shape[7] = -_height;

	m_position = _init_position;
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
	m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0.0f));
	m_position.y = m_position.y + _height;
	m_position.x = m_position.x + _width;
}

void Hero::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 0,0,1,1);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
}

void Hero::Move(glm::vec2 _movement)
{
	if (m_position.x + _movement.x < -1 ||
		m_position.x + _movement.x > 1	||
		m_position.y + _movement.y < -1 ||
		m_position.y + _movement.y > 1)
	{
		return;
	}
	m_translate = _movement;
	//if(m_translate.x > 0) // Giro a derecha
	//{
	//	m_model = glm::rotate(m_model,glm::radians(90.f), glm::vec3(1,1,0));
	//}
	//else if(m_translate.x < 0) // Giro a izquierda
	//{
	//	m_model = glm::rotate(m_model, glm::radians(-90.f), glm::vec3(-1, -1, 0));
	//}
	m_position += m_translate;
	m_model = glm::translate(m_model, glm::vec3(m_translate.x, m_translate.y, 0.0f));
	m_translate = glm::vec2(0.0f);
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

void Hero::SetNextPosition(glm::vec2 _next_position)
{
	m_next_position += _next_position;
}
