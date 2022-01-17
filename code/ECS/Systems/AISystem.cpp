#include "AISystem.h"

void AISystem::Update(Entity* _hero, std::vector<Entity*> _friendos)
{
	for (auto entity : _friendos )
	{
		entity->UpdateIA(_hero);
	}
}
