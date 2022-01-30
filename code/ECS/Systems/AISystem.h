#pragma once
#include <vector>
#include "../Entities/Entity.h"

class AISystem
{
public:
	AISystem(){}
	void Update(Entity* _hero, std::vector<Entity*> _friendos);
};

