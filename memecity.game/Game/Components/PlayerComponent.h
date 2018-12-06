﻿#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>
#include <algorithm> // copy
#include "StoryComponent.h"

struct PlayerComponent : public memecity::engine::ecs::Component
{
	std::vector<const memecity::engine::ecs::Entity*> _stories;


	PlayerComponent(memecity::engine::ecs::Entity& entity, std::vector<const memecity::engine::ecs::Entity*> stories) : memecity::engine::ecs::Component(entity), _stories(stories) {};
};

#endif;
