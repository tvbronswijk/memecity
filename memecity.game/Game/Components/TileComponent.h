#ifndef _TILE_COMPONENT_H
#define _TILE_COMPONENT_H
#include <ECS.h>

struct TileComponent : public memecity::engine::ecs::Component
{
	const char* type;
	bool blocked, block_sight;
	TileComponent(memecity::engine::ecs::Entity& entity, const char* type, bool blocked, bool block_sight) 
		: memecity::engine::ecs::Component(entity), type(type), blocked(blocked), block_sight(block_sight) {}
};

#endif
