#include "AIComponent.h"

glm::vec2 AIComponent::Update(glm::vec2 _target_position,
	glm::vec2 _current_position)
{
	glm::vec2 direction_forward = glm::vec2(
		_target_position.x - _current_position.x,
		_target_position.y - _current_position.y
		);
	glm::vec2 direction_backward = glm::vec2(
		_target_position.x - _current_position.x,
		_target_position.y - _current_position.y
	);
	direction_forward = glm::normalize(direction_forward);
	direction_backward = glm::normalize(direction_backward);
	auto direction = rand() % 200 > 100.f ? direction_backward : direction_forward;
	glm::vec2 move_to = glm::vec2(0.005f * direction.x,
		0.005f * direction.y);
	return move_to;
}
