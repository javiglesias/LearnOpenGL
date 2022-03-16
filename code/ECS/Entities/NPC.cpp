#include "NPC.h"

NPC::NPC(glm::vec2 _init_position, float _width, float _height)
{
	m_position = _init_position;
	m_shape_size = Shape_Size(_width, _height);
	m_position.x = m_position.x - m_shape_size.w;
	m_position.y = m_position.y - m_shape_size.h;
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
	m_rigidbody = new PhysicsComponent(m_position, 0.02f, 0.05f);
	m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0.0f));
}

void NPC::Draw()
{
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 0, 1, 0, 1);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
}
void NPC::Move(glm::vec2 _scrolling)
{
	m_position	-= _scrolling;
	m_translate -= _scrolling;
	m_model = glm::translate(m_model, glm::vec3(m_translate.x,
		m_translate.y, 0.0f));
	m_translate = glm::vec2(0.0f);
}

void NPC::UpdatePhysics()
{
}

bool NPC::UpdatePhysics(Entity* _target, bool _interacting, void (*_callback) ())
{
	if (_target->GetPosition().x < (m_position.x + m_shape_size.w) &&
		_target->GetPosition().x >= m_position.x &&
		_target->GetPosition().y < (m_position.y + m_shape_size.h) &&
		_target->GetPosition().y >= m_position.y)
	{
		// llamada de callback cuando ha hablado con el NPC
		(*_callback)();
		return true;
	}
	if(_interacting)
	{
		fprintf(stdout, "NPC: (%.3f,%.3f)\n", m_position.x, m_position.y);
		fprintf(stdout, "NPC: (%.3fx%.3f)\n", m_position.x + m_shape_size.w,
			m_position.y + m_shape_size.h);
	}
	return false;
}

void NPC::UpdateSounds()
{
}

glm::vec2 NPC::GetPosition()
{
	return m_position;
}

glm::vec2 NPC::GetNextPosition()
{
	return glm::vec2();
}

