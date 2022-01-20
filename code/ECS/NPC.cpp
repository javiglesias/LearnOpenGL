#include "NPC.h"

NPC::NPC(Shader* _shader, glm::vec2 _init_position, float _width, float _height)
{
	m_width = _width;
	m_height = _height;
	m_position = _init_position;
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
	m_rigidbody = new PhysicsComponent(m_position, 0.02f, 0.05f);
}

void NPC::Draw(glm::vec2 _scrolling)
{
	m_translate -= _scrolling;
	glBindVertexArray(VAO);
	glUniform4f(base_color_id, 0, 1, 0, 1);
	m_model = glm::translate(m_model, glm::vec3(m_translate.x, 
		m_translate.y, 0.0f));
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	m_translate = glm::vec2(0.0f);
	shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shader->unuse();
	//DrawEffectArea();
}
void NPC::DrawEffectArea()
{
	glBindVertexArray(VAO_Circle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Circle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_collision_shape), 
		m_collision_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	glUniform4f(base_color_id, 1, 1, 1, 1);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(m_model));
	shader->use();
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	shader->unuse();
}

void NPC::UpdatePhysics()
{
}

void NPC::UpdateSounds()
{
}

glm::vec2 NPC::GetPosition()
{
	return glm::vec2();
}

glm::vec2 NPC::GetNextPosition()
{
	return glm::vec2();
}

