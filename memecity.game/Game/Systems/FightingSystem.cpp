#include "FightingSystem.h"

using namespace memecity::engine::ecs;


void FightingSystem::run(EntityManager &em) const {
}

void FightingSystem::on_attack(EntityManager &em, AttackEventArgs args) {
	auto drawable_health_target = args.target.get<HealthComponent>();
	auto health_target = args.target.get<HealthComponent>();
	auto AI = args.target.get<AIComponent>();

	
	drawable_health_target->health -= 10;
	health_event.fire(em, { drawable_health_target->health });

	std::string hp = "HP: ";
	if (drawable_health_target->health > 10) {
		health_target->health -= 10;
		hp += std::to_string(drawable_health_target->health);
	}else {
		drawable_health_target->health = 0;
		hp += std::to_string(drawable_health_target->health);
	}
	hp += "/";
	hp += std::to_string(drawable_health_target->maxhealth);

	if (drawable_health_target->health > (drawable_health_target->maxhealth / 2)) {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&drawable_health_target->get_texture());
		auto target_health_texture = multimedia_manager.get_text_texture(hp, "Fonts/Minecraftia-Regular.ttf", 10, { 34,139,34 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		drawable_health_target->texture = std::move(target_health_texture);
	}
	else if (drawable_health_target->health < (drawable_health_target->maxhealth / 2) && drawable_health_target->health > 0) {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&drawable_health_target->get_texture());
		auto target_health_texture = multimedia_manager.get_text_texture(hp, "Fonts/Minecraftia-Regular.ttf", 10, { 255,140,0 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		drawable_health_target->texture = std::move(target_health_texture);
	}
	else {
		auto text_health_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&drawable_health_target->get_texture());
		auto target_health_texture = multimedia_manager.get_text_texture(hp, "Fonts/Minecraftia-Regular.ttf", 10, { 220,20,60 });
		target_health_texture->set_position({ 0, -20 });
		target_health_texture->set_parent(text_health_texture->get_parent());
		drawable_health_target->texture = std::move(target_health_texture);
	}

	if (AI != nullptr) {
		AI->state = AIComponent::State::Fighting;
	}
}
