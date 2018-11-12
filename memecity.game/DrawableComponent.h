﻿#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H
#include <ECS.h>
#include "Engine\Textures\Texture.h"

struct DrawableComponent : public memecity::engine::ecs::Component
{
private:
	std::unique_ptr<memecity::engine::texture::Texture> texture;

public:
	DrawableComponent(const memecity::engine::ecs::Entity& entity)
		: DrawableComponent(entity, nullptr) {}
	DrawableComponent(const memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture)
		: memecity::engine::ecs::Component(entity), texture(std::move(texture)){}
	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
};

#endif

