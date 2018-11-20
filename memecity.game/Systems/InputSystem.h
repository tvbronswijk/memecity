﻿#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include <Engine\InputManager.h>
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\AttackEventArgs.h"
#include "..\Event\InteractionEventArgs.h"

class InputSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::InputManager& input_manager;
	bool check_collision(memecity::engine::ecs::EntityManager& em, memecity::engine::ecs::Component& element, int range) const;
public:
	memecity::engine::ecs::eventing::Event<InteractionEventArgs> interaction_event;
	memecity::engine::ecs::eventing::Event<AttackEventArgs> attack_event;

	InputSystem(memecity::engine::InputManager& input_manager)
		: input_manager(input_manager) {};
	void run(memecity::engine::ecs::EntityManager& em) const override;
};
#endif