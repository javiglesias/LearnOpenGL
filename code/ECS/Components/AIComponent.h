#pragma once
#include "glm.hpp"
class AIComponent
{
public:
	AIComponent() {}
	glm::vec2 virtual Update(glm::vec2 _target_position,
		glm::vec2 _current_position);
private:
	float new_x = 0, new_y = 0;
	float increment_x = 0.01;
	float increment_y = 0.01;
};

