#pragma once
#include "Entity.h"
class Hero :
    public Entity
{

public:
    Hero(){}
    Hero(Shader* _shader, glm::vec2 _position = glm::vec2(0,0));
	void Draw() override;
	float shape[15] = {
		//	x,y,z
		0.0f, 0.0f, 0.0f,
		-0.02f, -0.05f, 0.0f,
		0.02f, -0.05f, 0.0f,
		0.0f, 0.0f, 0.0f	
	};
	void Move(glm::vec2 _movement) override;
	void UpdatePhysics() override;
	void UpdateSounds() override;
	glm::vec2 GetPosition() override;
	glm::vec2 GetNextPosition() override;
	Shape_Size GetSize() override;
	void SetNextPosition(glm::vec2);
	PhysicsComponent* GetPhysicsComponent() override { return m_rigidbody; };
private:
	unsigned int model_id = -1;
	unsigned int base_color_id = -1;
	unsigned int VBO;
	unsigned int VAO = -1;
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::vec2 m_position{0.f};
	glm::vec2 m_next_position{0.f};
	glm::vec2 m_center {0.f};
	glm::vec2 m_translate{0.f};
	float m_width = 0.02f;
	float m_height = 0.05f;
	Shader* shader;
	PhysicsComponent* m_rigidbody{};
	SoundComponent* m_ears;
};

