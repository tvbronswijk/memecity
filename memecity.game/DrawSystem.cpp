﻿#include "DrawSystem.h"

std::string DrawSystem::SYSTEM_TYPE = "DrawSystem";

DrawSystem::DrawSystem(MultimediaManager &multimedia_manager) : multimedia_manager(multimedia_manager)
{
}


void DrawSystem::run(EntityManager& em)
{
	auto player_components = em.get_components_of_type(PlayerComponent::COMPONENT_TYPE);
	auto player_position_component = dynamic_cast<PositionComponent*>(em.get_component_of_entity(player_components[0]->entity_id, PositionComponent::COMPONENT_TYPE));

	auto drawable_components = em.get_components_of_type(DrawableComponent::COMPONENT_TYPE);

	for (auto drawable_component : drawable_components)
	{
		if (drawable_component->entity_id != player_position_component->entity_id)
		{
			auto tex = dynamic_cast<DrawableComponent*>(drawable_component)->texture;
			tex->translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}
	}

	multimedia_manager.clear_graphics();
	for (Component* component : drawable_components)
	{
		dynamic_cast<DrawableComponent*>(component)->texture->render();
	}
	multimedia_manager.render_graphics();
}

std::string DrawSystem::get_type()
{
	return SYSTEM_TYPE;
}


void DrawSystem::run(EntityManager& em, EventArgs& e)
{
}

