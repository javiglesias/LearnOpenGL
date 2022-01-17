#include "Monster.h"

Monster::Monster(Shader* _shader, glm::vec2 _init_position)
{
	m_brain = new AIComponent();
	m_ears = new SoundComponent();
	m_rigidbody = new PhysicsComponent(m_position, m_width, m_height);
	shader = _shader;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_Circle);
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO_Circle);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape), shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	model_id = glGetUniformLocation(shader->id, "model");
	base_color_id = glGetUniformLocation(shader->id, "base_color");
	//	Posicion de inicio donde va a empezar el enemigo
	m_model = glm::translate(m_model, glm::vec3(_init_position.x, _init_position.y, 0.0f));
	m_position = _init_position;
	m_center.x = m_position.x;
	m_center.y = m_position.y - 0.025f;
}

void Monster::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 0, 1, 1, 1);
	m_model = glm::translate(m_model, glm::vec3(m_translate.x, m_translate.y, 0.0f));
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
	DrawEffectArea();
	m_translate = glm::vec2(0.f);
}

void Monster::DrawEffectArea()
{
	glBindVertexArray(VAO_Circle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Circle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_points), circle_points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	glUniform4f(base_color_id, 1, 1, 1, 1);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	shader->unuse();
}

void Monster::Move(glm::vec2 _movement)
{
	if (m_center.x + _movement.x < -1	||
		m_center.x + _movement.x > 1	||
		m_center.y + _movement.y < -1	||
		m_center.y + _movement.y > 1)
	{
		return;
	}
	m_translate = _movement;
	m_position += _movement;
}

void Monster::UpdateIA(Entity* _hero)
{
	//	Aqui se hacen todas las actualizaciones de IA necesarias, movimiento, accion a tomar
	//	Esto se esta ejecutando a 24fps
	glm::vec2 movement = m_brain->Update(_hero->GetPosition(), m_position);
	Move(movement);
}

PhysicsComponent* Monster::GetPhysicsComponent()
{
	return m_rigidbody;
}

glm::vec2 Monster::GetPosition()
{
	return m_position;
}
