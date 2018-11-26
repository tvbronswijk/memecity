﻿#include "InputSystem.h"
#include "..\Components.h"
#include "..\States.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

bool InputSystem::check_collision(EntityManager& em, Component& element , int range) const{
	auto player = em.get_components_of_type<PlayerComponent>()[0];
	auto player_position_component = player.get().entity().get<PositionComponent>();
	auto xy = element.entity().get<PositionComponent>();
	if ((player_position_component->x + range) >= xy->x && (player_position_component->x - range) <= xy->x) {
		if ((player_position_component->y + range) >= xy->y && (player_position_component->y - range) <= xy->y) {
			return true;
		}
	}
	return false;
}

void InputSystem::run(EntityManager& em) const
{
	auto& input_manager = _context->get_input_manager();
	auto& state_manager = _context->get_state_manager();

	auto entities = em.get_entities_with_component<PlayerComponent>();
	for (const Entity& entity : entities)
	{
		auto velocity_component = entity.get<VelocityComponent>();

		if (input_manager.is_down(sdl::Attack))
		{
			const auto animation_component = entity.get<AnimationComponent>();
			if (animation_component)
			{
				animation_component->current_state = AnimationComponent::AnimationState::fighting;
			}
		}
		if (input_manager.is_down(sdl::Up))
		{
			velocity_component->y -= 0.1f;
		}
		if (input_manager.is_down(sdl::Down))
		{
			velocity_component->y += 0.1f;
		}
		if (input_manager.is_down(sdl::Left))
		{
			velocity_component->x -= 0.1f;
		}
		if (input_manager.is_down(sdl::Right))
		{
			velocity_component->x += 0.1f;
		}
		//test for interaction with NPC
		if (input_manager.is_down(sdl::Interaction))
		{
			auto vector = em.get_components_of_type<AIComponent>();
			for (AIComponent& element : vector) {
				if(check_collision(em, element, 9999999990)){
					interaction_event.fire(em, { element.entity() });
				}
			}
		}
		if (input_manager.is_pressed(sdl::Attack)) {
			auto& player = em.get_components_of_type<PlayerComponent>()[0].get();
			auto vector = em.get_components_of_type<AIComponent>();
			for (AIComponent& element : vector) {
				if (check_collision(em, element, 9999999990)) {
					attack_event.fire(em, {player.entity(), element.entity() });
				}
			}
		}
		if (input_manager.is_pressed(sdl::Escape)) {
			state_manager.create_state<PauseMenuState>(*_context);
		}
	}
}

