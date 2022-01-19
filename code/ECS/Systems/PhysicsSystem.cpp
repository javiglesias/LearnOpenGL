#include "PhysicsSystem.h"

void PhysicsSystem::UpdatePhysics()
{
	return;
}

void PhysicsSystem::AddStaticWorld(Entity* _entity)
{
	m_static_world.push_back(_entity);
}

void PhysicsSystem::AddDynamicWorld(Entity* _entity)
{
	m_dynamic_world.push_back(_entity);
}

bool PhysicsSystem::GonnaCollideWith(Entity* _entity)
{
	for (auto static_entity : m_static_world)
	{
		if (_entity->GetNextPosition() == static_entity->GetPosition())
		{
			return true;
		}
		else if (static_entity->GetPhysicsComponent()->IsCollidingWith(_entity->GetNextPosition()))
		{
			return true;
		}
	}
	return false;
}
/// <summary>
/// 
/// </summary>
/// <param name="_one">hero</param>
/// <param name="_two">door</param>
/// <returns></returns>
bool PhysicsSystem::GonnaCollide(Entity* _one, Entity* _two)
{
	auto _one_rigidbody = _one->GetPhysicsComponent();
	auto _two_rigidbody = _two->GetPhysicsComponent();
	if(_one_rigidbody->m_position.x < (_two_rigidbody->m_position.x + _two_rigidbody->m_width) &&
		_one_rigidbody->m_position.x > _two_rigidbody->m_position.x &&
		_one_rigidbody->m_position.y < (_two_rigidbody->m_position.y + _two_rigidbody->m_height) &&
		_one_rigidbody->m_position.y > _two_rigidbody->m_position.y)
		return true;
	else
		return false;	
}

void PhysicsSystem::FreeOutOfBounds(std::vector<Entity*> *_entities)
{
	for (auto _entity : *_entities)
	{
		if (_entity->GetPosition().x > bound_right_top ||
			_entity->GetPosition().x < bound_left_bottom ||
			_entity->GetPosition().y > bound_right_top ||
			_entity->GetPosition().y < bound_left_bottom)
		{
			if(!_entity->m_to_delete)
			{
				_entity->m_to_delete = true;
				_entity->m_show = false;
			}
		}
	}
}

void PhysicsSystem::IsColliding(Entity* _one, std::vector<Entity*> _entities)
{
	//	Aqui hay que recorrer todas las entidades que se le pasan y comprobar si esta colisionando con alguna de ellas.
	for (auto _entity : _entities)
	{
		if (_one->GetNextPosition().x > _entity->GetPosition().x + 0.1 &&
			_one->GetNextPosition().x < _entity->GetPosition().x + 0.1 &&
			_one->GetNextPosition().y > _entity->GetPosition().y + 0.1 &&
			_one->GetNextPosition().y < _entity->GetPosition().y + 0.1)
		{
			fprintf(stdout, "Colisiono con algo");
		}
	}
}
