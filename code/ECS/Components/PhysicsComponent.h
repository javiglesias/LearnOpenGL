#pragma once
#include "glm.hpp"
class PhysicsComponent
{
public:
	PhysicsComponent(glm::vec2 _position, float _width, float _height, bool _static = true)
	{ 
		m_position = _position;
		m_width = _width;
		m_height = _height;
		m_is_static = _static;
	}
	void virtual UpdatePhysics();
	void virtual UpdatePosition(glm::vec2);
	bool IsCollidingWith(glm::vec2);
	float m_width, m_height;
	glm::vec2 m_position;
private:
	bool m_is_static = true;
};

