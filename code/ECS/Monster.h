#pragma once
#include "Entity.h"
class Monster : public Entity
{
public:
	Monster(){}
	Monster(Shader* _shader, glm::vec2 _init_position = glm::vec2(0.0f));
	float shape[15] = {
		//	x,y,z
		0.0f, 0.0f, 0.0f,
		-0.02f, -0.05f, 0.0f,
		0.02f, -0.05f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
	float circle_points[15] = {
		//0.1f, 0.0f, 0.0f,
		0.1f, -0.1f, 0.0f,

		//0.0f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,

		//-0.1f, 0.0f, 0.0f,
		-0.1f, 0.1f, 0.0f,

		//0.0f, 0.1f, 0.0f,
		0.1f, 0.1f, 0.0f
	};
	void Draw() override;
	void DrawEffectArea() override;
	void Move(glm::vec2 _movement) override;
	void UpdateIA(Entity* _hero) override;
	PhysicsComponent* GetPhysicsComponent() override;
	glm::vec2 GetPosition() override;
	PhysicsComponent* m_rigidbody;
private:
	unsigned int VBO = -1, VBO_Circle = -1;
	unsigned int VAO = -1, VAO_Circle = -1;
	unsigned int m_radius = 0.1f;
	glm::vec2 m_position{ 0,0 };
	glm::vec2 m_center{ 0,0 };
	glm::vec2 m_translate{ 0,0 };
	float m_width = 0.02f;
	float m_height = 0.05f;
	int m_tex_width, m_tex_height, m_tex_channels;
	unsigned int m_texture = -1;
	unsigned char* m_tex_data;
	glm::mat4 m_model = glm::mat4(1.0f);
	unsigned int model_id = -1;
	unsigned int base_color_id = -1;
	AIComponent* m_brain;
	Shader* shader;
	SoundComponent* m_ears;
	float m_active_distance = 0.1f;
};

