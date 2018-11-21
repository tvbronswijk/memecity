#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H
#include <ECS.h>
#include <string>
#include "LevelComponent.h"

struct StatsComponent: public memecity::engine::ecs::Component
{
	int strength, perception, endurance, charisma, intelligence, agility, luck;
	StatsComponent(const memecity::engine::ecs::Entity& entity) : StatsComponent(entity, 5, 5, 5, 5, 5, 5, 5) {};
	StatsComponent(const memecity::engine::ecs::Entity& entity, int strength, int perception, int endurance, int charisma, int intelligence, int agility, int luck)
		: memecity::engine::ecs::Component(entity), strength(strength), perception(perception), endurance(endurance), charisma(charisma), intelligence(intelligence), agility(agility), luck(luck) { };

};

#endif
