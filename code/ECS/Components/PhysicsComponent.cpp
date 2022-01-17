#include "PhysicsComponent.h"

void PhysicsComponent::UpdatePhysics()
{
	m_position = glm::vec2(0.f);
	return;
}

void PhysicsComponent::UpdatePosition(glm::vec2 _position)
{
	m_position = _position;
}

bool PhysicsComponent::IsCollidingWith(glm::vec2 _other)
{
	float x_center = m_position.x + m_width/2;
	float y_center = m_position.y + m_height/2;
	// TOP < and > BOTTOM and LEFT > and < RIGHT
	fprintf(stdout, "colisionando\n");
	return false;
}
