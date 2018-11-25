#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
#include "StatsComponent.h"
#include "DrawableComponent.h"

struct HealthComponent : public memecity::engine::ecs::Component{
public:
	int maxhealth;
	int health;

	std::unique_ptr<memecity::engine::texture::Texture> texture;

	HealthComponent(memecity::engine::ecs::Entity& entity)
		: HealthComponent(entity,0, nullptr) {}
	HealthComponent(memecity::engine::ecs::Entity& entity,int health, std::unique_ptr<memecity::engine::texture::Texture> texture)
		: memecity::engine::ecs::Component(entity), maxhealth(health),health(health), texture(std::move(texture)) {}

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
};

#endif