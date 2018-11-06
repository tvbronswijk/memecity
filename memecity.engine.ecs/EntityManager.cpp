#include "EntityManager.h"

ecs::EntityManager::EntityManager()
{

}

ecs::Entity* ecs::EntityManager::create_entity()
{
	auto e = new ecs::Entity(id++);
	entities.push_back(e);
	return e;
}

void ecs::EntityManager::register_component(ecs::Component* c)
{
	components[c->get_type_token()].push_back(c);
}

void ecs::EntityManager::register_system(ecs::System* s)
{
	systems[s->get_type_token()] = s;
}

std::vector<ecs::Entity*> ecs::EntityManager::get_entities()
{
	return entities;
}

std::vector<ecs::Entity*> ecs::EntityManager::get_entities_with_component(component_typetoken type)
{
	std::vector<ecs::Entity*> result;
	for (auto it = entities.begin(); it != entities.end(); ++it)
		if (this->has_component(*it, type))
			result.push_back(*it);
	return result;
}

std::vector<ecs::Component*> ecs::EntityManager::get_components_of_type(component_typetoken type)
{
	return components[type];
}

ecs::Component* ecs::EntityManager::get_component_of_entity(int entity_id, component_typetoken token)
{
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == entity_id && c->get_type_token() == token)
				return c;
	return nullptr;
}

std::vector<ecs::Component*> ecs::EntityManager::get_components_of_entity(int entity_id)
{
	std::vector<ecs::Component*> result;
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == entity_id)
				result.push_back(c);
	return result;
}

bool ecs::EntityManager::has_component(ecs::Entity* e, component_typetoken type)
{
	auto c = components[type];
	for (auto it = c.begin(); it != c.end(); ++it)
		if ((*it)->entity_id == e->id)
			return true;
	return false;
}

void ecs::EntityManager::update() 
{
	for (auto pair : systems)
		pair.second->run(*this);
}

ecs::EntityManager::~EntityManager()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
		delete(*it);
	entities.clear();

	for (auto pair : components)
	{
		for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
			delete(*it);
		pair.second.clear();
	}
	components.clear();

	for (auto it = systems.begin(); it != systems.end(); ++it)
		delete (it->second);
	systems.clear();
}
