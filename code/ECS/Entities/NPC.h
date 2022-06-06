#pragma once
#include "Entity.h"

class NPC : public Entity
{
public:
	NPC(){ Entity::m_name = "dummyNPC"; }
	NPC(glm::vec2 _init_position, float _width = 0.025f, float _height = 0.025f);
	~NPC();
	void Draw() override;
	void Move(glm::vec2 _scrolling) override;
	void UpdatePhysics() override;
	bool UpdatePhysics(Entity* _hero, bool _interacting, void (*_callback) ());
	void UpdateSounds() override;
	glm::vec2 GetPosition() override;
	void SetPosition(glm::vec2 _newPosition) override;
	glm::vec2 GetNextPosition() override;
	PhysicsComponent* GetPhysicsComponent() override { return m_rigidbody; };
private:
	unsigned int model_id = -1;
	unsigned int base_color_id = -1;
	unsigned int VBO = -1, VBO_Circle = -1;
	unsigned int VAO = -1, VAO_Circle = -1;
	float m_width = 0.05f;
	float m_height = 0.05f;
	Shader* shader = new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "NPC");
	Shape_Size* m_shape_size;
	PhysicsComponent* m_rigidbody{};
	SoundComponent* m_ears;
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::vec2 m_translate{ 0.f };
	glm::vec2 m_next_position{ 0.f };
	float shape[15] = {
		//	x,y,z
		0.0f, 0.0f, 0.0f,
		-0.02f, -0.05f, 0.0f,
		0.02f, -0.05f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
	float m_collision_shape[15] = {
		0.05f, -0.05f, 0.0f,
		-0.05f, -0.05f, 0.0f,
		-0.05f, 0.05f, 0.0f,
		0.05f, 0.05f, 0.0f
	};
};

