#include "Room.h"


Room::Room(glm::vec2 _init_position, float _width, float _height)
{
	Entity::m_position = _init_position;
	m_shape_size = Shape_Size(_width, _height);
	// witdth
	m_shape[6] = _width;
	m_shape[9] = _width;
	m_shape[15] = _width;
	//height
	m_shape[4] = _height;
	m_shape[13] = _height;
	m_shape[16] = _height;

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

	m_model = glm::translate(m_model, glm::vec3(Entity::m_position.x, Entity::m_position.y, 0));
	Entity::m_position.x = _init_position.x + _width / 2;
	Entity::m_position.y = _init_position.y + _height / 2;
}

PhysicsComponent* Room::GetPhysicsComponent()
{
	return m_rigidbody;
}

void Room::Draw()
{
	glBindVertexArray(VAO);
	SetShaderColor(m_shader_base_color);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_shader->unuse();
}
void Room::Move(glm::vec2 _scrolling)
{
	m_movement -= _scrolling;
	Entity::m_position -= _scrolling;
	m_model = glm::translate(m_model, glm::vec3(m_movement.x, m_movement.y, 0));
	m_movement = glm::vec2(0.f);
}


void Room::UpdateGraphics(Color _color)
{
	m_shader_base_color = _color;
	SetShaderColor(m_shader_base_color);
}

void Room::UpdatePhysics()
{
	m_rigidbody->UpdatePhysics();
}

bool Room::UpdatePhysics(Entity* _target)
{
	if (_target->GetPosition().x < (Entity::m_position.x + m_shape_size.w) &&
		_target->GetPosition().x >= Entity::m_position.x &&
		_target->GetPosition().y < (Entity::m_position.y + m_shape_size.h) &&
		_target->GetPosition().y >= Entity::m_position.y)
	{
		fprintf(stdout, "wall collide");
		return true;
	}
	return false;
}

glm::vec2 Room::GetPosition()
{
	return Entity::m_position;
}

void Room::UpdateIA()
{
	/*float increment = 0.0001f;
	if (Entity::m_position.x >= .9f)
	{
		increment = -sin(rand() % 2 / 10.f);
	}
	else if (Entity::m_position.x <= -.9f)
	{
		increment = sin(rand() % 2 / 10.f);
	}
	m_movement.x += increment;*/
}

void Room::SetShaderColor(Color _color)
{
	glUniform4f(base_color_id, _color.r, _color.g, _color.b, _color.a);
}
