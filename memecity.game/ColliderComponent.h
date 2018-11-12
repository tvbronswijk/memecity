#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H
#include "ECS.h"

struct ColliderComponent : public memecity::engine::ecs::Component
{
	int w, h;

	ColliderComponent(const memecity::engine::ecs::Entity& entity) : ColliderComponent(entity, 0, 0) {};
	ColliderComponent(const memecity::engine::ecs::Entity& entity, int w, int h)
		: memecity::engine::ecs::Component(entity), w(w), h(h) {};
};

#endif
