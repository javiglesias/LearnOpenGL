#pragma once
#include <vector>
#include "../Entity.h"
class PhysicsSystem
{
public:
	PhysicsSystem(){};
	void UpdatePhysics();
	void AddStaticWorld(Entity*);
	void AddDynamicWorld(Entity*);
	bool GonnaCollideWith(Entity*);
	bool GonnaCollide(Entity* _one, Entity* _two);
	void FreeOutOfBounds(std::vector<Entity*>*);
	void IsColliding(Entity* _entity, std::vector<Entity*> _collisionable_world);
private:
	std::vector<Entity*> m_static_world{};	//	Colisiones estaticas
	std::vector<Entity*> m_dynamic_world{};
	float bound_left_bottom = -0.99f;
	float bound_right_top = 0.99f;
};

