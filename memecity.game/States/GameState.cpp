#include "GameState.h"
#include "..\Components.h"
#include "..\Systems.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

void GameState::on_load()
{
	auto& multimedia_manager = _context->multimedia_manager;
	auto& input_manager = _context->input_manager;
	auto& timer = _context->timer;

	city_generator.generate(16, 16, entity_manager, multimedia_manager);

	auto texture = multimedia_manager.get_animated_texture(timer, "SpriteSheet.png", 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });
	auto& player = builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<PlayerComponent>()
		.with_component<AnimationComponent>()
		.with_component<ColliderComponent>(48.0f, 48.0f)
		.with_component<PositionComponent>(0,0)
		.with_component<VelocityComponent>()
		.with_component<DrawableComponent>(std::move(texture))
		.get();


	auto text_texture = multimedia_manager.get_text_texture("Health: 500", "Minecraftia-Regular.ttf", 16, { 255,255,255 });
	text_texture->set_parent(&player.get<DrawableComponent>()->get_texture());
	text_texture->set_position({ 0, -30 });
	builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<DrawableComponent>(std::move(text_texture));


	//test to show an example  for a NPC
	for (size_t i = 0; i < 1; i++) {
		float x = player.get<PositionComponent>()->x;//TODO: change when position can be placed correctly
		float y = player.get<PositionComponent>()->y;//TODO: change when position can be placed correctly
		npc_factory.getRandomNPC(100, player.get<PositionComponent>()->x, player.get<PositionComponent>()->y);
	}
	auto& fighting_system = entity_manager.create_system<FightingSystem>(System::draw, multimedia_manager);
	entity_manager.create_system<AISystem>();
	auto& interaciton_system = entity_manager.create_system<InteractionSystem>(System::draw, multimedia_manager);
	auto& animation_system = entity_manager.create_system<AnimationSystem>(System::update);
	entity_manager.create_system<DrawSystem>(System::draw, multimedia_manager);
	auto& input_system = entity_manager.create_system<InputSystem>(System::update, input_manager, *_state_machine);
	auto& move_system = entity_manager.create_system<MoveSystem>();
	auto& collider_system = entity_manager.create_system<ColliderSystem>();
	entity_manager.create_system<OverlaySystem>(System::draw, multimedia_manager);

	// events
	ecs::eventing::bind(input_system.interaction_event,		&interaciton_system,	&InteractionSystem::on_interact);
	ecs::eventing::bind(move_system.move_event,				&animation_system,		&AnimationSystem::on_move);
	ecs::eventing::bind(input_system.attack_event,			&fighting_system,		&FightingSystem::on_attack);
	ecs::eventing::bind(collider_system.collider_event,		&move_system,			&MoveSystem::on_collision);
}

void GameState::update(float dt)
{
	entity_manager.update(System::update);
}

void GameState::draw()
{
	entity_manager.update(System::draw);
}

void GameState::on_enter()
{
	_context->multimedia_manager.play_background_music("bgm-game.mp3", 100);
}

void GameState::on_exit()
{
	
}
