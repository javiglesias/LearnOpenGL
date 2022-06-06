#pragma once
#include "Entity.h"
class Monster : public Entity
{
public:
	Monster(){ Entity::m_name = "dummyMonster"; }
	~Monster();
	Monster(glm::vec2 _init_position = glm::vec2(0.0f));
	// Tipos de enemigos que pueden spawnear a otros.
	void Draw() override;
	//void DrawEffectArea() override;
	void Move(glm::vec2 _movement) override;
	void UpdateIA(Entity* _hero) override;
	bool UpdatePhysics(Entity* target) override;
	PhysicsComponent* GetPhysicsComponent() override;
	glm::vec2 GetPosition() override;
	void SetPosition(glm::vec2 _newPosition) override;
	virtual Monster* Clone()
	{
		return new Monster(Entity::m_position);
	}
private:
	unsigned int VBO = -1, VBO_Circle = -1;
	unsigned int VAO = -1, VAO_Circle = -1;
	float m_radius = 0.1f;
	glm::vec2 m_center{ 0,0 };
	glm::vec2 m_translate{ 0,0 };
	int m_tex_width, m_tex_height, m_tex_channels;
	unsigned int m_texture = -1;
	unsigned char* m_tex_data;
	glm::mat4 m_model = glm::mat4(1.0f);
	unsigned int model_id = -1;
	unsigned int base_color_id = -1;
	unsigned int alive_id = -1;
	AIComponent* m_brain;
	Shader* shader = new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO");
	SoundComponent* m_ears;
	float m_active_distance = 0.1f;
	PhysicsComponent* m_rigidbody;
	float m_shape[15] = {
		//	x,y,z
		0.0f, 0.0f, 0.0f,
		-0.02f, -0.05f, 0.0f,
		0.02f, -0.05f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
};

