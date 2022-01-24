#pragma once

#include "../Render/Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../../dependencies/stb_image/stb_image.h"
#include "Components/PhysicsComponent.h"
#include "Components/AIComponent.h"
#include "Components/GraphicsComponent.h"
#include "Components/SoundComponent.h"
#include "Components/PhysicsComponent.h"


class Entity
{
public:
	struct Color
	{
		float r = 0.f, g = 0.f, b = 0.f, a = 1.f;
		Color(){}
		Color(float _r, float _g, float _b, float _a = 1.f) 
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
	};
	typedef struct Shape_Size
	{
		float w;
		float h;
		Shape_Size(float _w, float _h)
		{
			w = _w;
			h = _h;
		}
	} Shape_Size;
	enum MyColors
	{
		RED,
		GREEN,
		BLUE
	};
	Entity();
	void virtual Move(){};
	void virtual Draw(){};
	void virtual DrawEffectArea(){}
	void virtual LoadTexture(){};
	void virtual Move(glm::vec2 _movement);
	void virtual UpdateIA(Entity* _target) {}
	void virtual UpdateIA() {}
	void virtual UpdateAnimation(){}
	void virtual UpdateGraphics(Color _color){}
	void virtual UpdatePhysics(){}
	void virtual UpdateSounds(){}
	PhysicsComponent virtual *GetPhysicsComponent(){return nullptr;}
	glm::vec2 virtual GetPosition() 
	{
		return glm::vec2(0.0f);
	}
	glm::vec2 virtual GetNextPosition() 
	{
		return glm::vec2(0.0f);
	}
	Shape_Size virtual GetSize()
	{
		return m_size;
	}
	bool m_to_delete = false;
	bool m_show = true;
private:
	Shape_Size m_size{0.f, 0.f};
};

