#pragma once
#include "Entity.h"
class Hero :
    public Entity
{

public:
    Hero(){}
    Hero(glm::vec2 _position = glm::vec2(0,0),
		float _width = .04f, float _height = .02f);
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
	Shape_Size GetSize() override
	{
		return m_shape_size;
	}
	void SetNextPosition(glm::vec2);
	PhysicsComponent* GetPhysicsComponent() override { return m_rigidbody; };
	void Interact(bool _interacting){m_interacting = _interacting;}
	bool GetInteracting() {return m_interacting;}
private:
	unsigned int model_id = -1;
	unsigned int base_color_id = -1;
	unsigned int VBO;
	unsigned int VAO = -1;
	bool m_interacting = false;
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::vec2 m_position{0.f};
	glm::vec2 m_next_position{0.f};
	glm::vec2 m_center {0.f};
	glm::vec2 m_translate{0.f};
	float m_width = 0.02f;
	float m_height = 0.05f;
	std::string m_hero_name;
	Shader* shader = new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "HERO");
	Shape_Size m_shape_size;
	PhysicsComponent* m_rigidbody{};
	SoundComponent* m_ears;
};
