#include "LevelChangeState.h"
#include <UI/Menu/MenuBuilder.h>
#include "..\..\Assets.h"
#include "LoadingState.h"
#include "..\LevelBuilder.h"

LevelChangeState::LevelChangeState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, memecity::engine::ecs::EntityManager & em)
	:State(sm), _context(&gc), _entity_manager(&em)
{
	auto& player = em.get_entities_by_type("player").front().get();
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Station", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Go to Next City", nullptr, [&](auto& _) {
		Point start;
		
		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) {
			auto entities = em.query_all_entities().where([](const auto& e) { return e.type != "player";  }).to_vector();
			listener.set_text("Clearing State...");
			listener.set_max_value(100.0f);
			listener.set_current_value(0.0f);
			for (const auto& entity : entities) {
				em.remove_entity(entity);
				listener.increase_current_value(100.0f / entities.size());
			}
			back(); });
		
		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) { start = LevelBuilder(ctx, 1, 128, 128, false).build(em, listener, *new int(1)); back(); });//TODO tobi, hier het nummer van de map meegeven
		player.get<BaseComponent>()->location = start;
		back();
	})
		.with_menu_item("Go to Last City", nullptr, [&](auto& _) {

		back();
	})
		.get_menu();
}

void LevelChangeState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		menu->select();
	}
}

void LevelChangeState::draw()
{
	menu->render();
}