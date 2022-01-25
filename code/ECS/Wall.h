#pragma once
#include "Entity.h"
class Wall : public Entity
{
public:
	Wall() {}
	Wall( glm::vec2 _position, float _width, float _height, Shader* _shader, Color _color = Color(1,0,1));
	PhysicsComponent* GetPhysicsComponent() override;
	void SetShaderColor(Color _color);
	void UpdateGraphics(Color _color) override;
	void UpdatePhysics();
	glm::vec2 GetPosition() override;
	void UpdateIA() override;
	void Draw() override;
	void Move(glm::vec2 _scrolling) override;
	Shape_Size GetSize() override
	{
		return m_shape_size;	
	}
private:
	float m_shape[18] = {
		0.1f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		-0.1f, 0.1f, 0.0f,
		//	1er triangulo
		-0.1f, 0.1f, 0.0f,
		0.1f, 0.1f, 0.0f,
		0.1f, -0.1f, 0.0f
		//	2nd triangulo
	};
	unsigned int VBO = -1;
	unsigned int VAO = -1;
	unsigned int base_color_id = -1;
	unsigned int model_id = -1;
	glm::mat4 m_model{1.0f};
	Shader* m_shader;
	Color m_shader_base_color;
	Shape_Size m_shape_size;
	glm::vec2 m_position{0.f};
	glm::vec2 m_movement{0.f};
	PhysicsComponent* m_rigidbody;
};	

