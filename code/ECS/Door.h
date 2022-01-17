#pragma once
#include "Entity.h"
class Door : public Entity
{
public:
	Door(){}
	Door(Shader* _shader, glm::vec2 _init_position);
	void Draw() override;
	glm::vec2 GetPosition() override;
	PhysicsComponent* GetPhysicsComponent() override {return m_rigidbody;};
private:
	float m_shape[15] = {
		 0.05f, -0.05f, 0.0f,
		-0.05f, -0.05f, 0.0f,
		-0.05f,  0.05f, 0.0f,
		 0.05f,  0.05f, 0.0f
	};
	glm::vec2 m_position;
	unsigned int VBO = -1;
	unsigned int VAO = -1;
	unsigned int m_model_id = -1;
	unsigned int m_base_color_id = -1;
	glm::mat4 m_model{1.0f};
	Shader* m_shader;
	PhysicsComponent* m_rigidbody{};
};

