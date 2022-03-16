#include "Monster.h"

Monster::Monster(glm::vec2 _init_position)
{
	m_brain = new AIComponent();
	m_ears = new SoundComponent();
	m_rigidbody = new PhysicsComponent(m_position, m_width, m_height);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_Circle);
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO_Circle);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_shape), m_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	model_id = glGetUniformLocation(shader->id, "model");
	base_color_id = glGetUniformLocation(shader->id, "base_color");
	alive_id = glGetUniformLocation(shader->id, "is_alive");
	//	Posicion de inicio donde va a empezar el enemigo
	m_model = glm::translate(m_model, glm::vec3(_init_position.x, _init_position.y, 0.0f));
	m_position = _init_position;
	m_shape_size = new Shape_Size(0.1f, 0.1f);
}

void Monster::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 1, 0, 0, 1);
	glUniform1i(alive_id, (int)!m_show);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
	//DrawEffectArea();

}

//void Monster::DrawEffectArea()
//{
//	glBindVertexArray(VAO_Circle);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_Circle);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_points), circle_points, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//		(void*)0);
//	glEnableVertexAttribArray(0);
//	glUniform4f(base_color_id, 1, 1, 1, 1);
//	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
//	shader->use();
//	glDrawArrays(GL_LINE_LOOP, 0, 4);
//	shader->unuse();
//}

void Monster::Move(glm::vec2 _scrolling)
{
	m_position	-= _scrolling;
	m_model = glm::translate(m_model, glm::vec3(-_scrolling.x, -_scrolling.y, 0.0f));
}

void Monster::UpdateIA(Entity* _hero)
{
	//	Aqui se hacen todas las actualizaciones de IA necesarias, movimiento, accion a tomar
	//	Esto se esta ejecutando a 24fps
	auto distance = glm::distance(_hero->GetPosition(), m_position);
	if (distance >= m_active_distance)
	{
		glm::vec2 movement = -m_brain->Update(_hero->GetPosition(), m_position);
		m_position = movement;
		//m_model = glm::translate(m_model, glm::vec3(movement.x, movement.y, 0.0f));
	}
}

bool Monster::UpdatePhysics(Entity* _target)
{
	if (_target->GetPosition().x < (m_position.x + m_shape_size->w) &&
		_target->GetPosition().x >= m_position.x &&
		_target->GetPosition().y < (m_position.y + m_shape_size->h) &&
		_target->GetPosition().y >= m_position.y)
	{
		m_show = false;
		return true;	
	}
	return false;
}

PhysicsComponent* Monster::GetPhysicsComponent()
{
	return m_rigidbody;
}

glm::vec2 Monster::GetPosition()
{
	return m_position;
}
