﻿#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc)
	: State(sm), _context(&gc)
{
	help_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Help")
		.with_read_only_menu_item("Controls:")
		.with_read_only_menu_item("W: Up")
		.with_read_only_menu_item("S: Down")
		.with_read_only_menu_item("A: Left")
		.with_read_only_menu_item("D: Right")
		.with_read_only_menu_item("E: Interact")
		.with_read_only_menu_item("Space: Attack")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Goal:")
		.with_read_only_menu_item("Kill NPCs to gain XP.")
		.with_read_only_menu_item("Interact with NPCs to start quests.")
		.with_read_only_menu_item("Complete quests to gain more XP.")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Die or click Retire to finish the game.")
		.with_read_only_menu_item(" ")
		.with_back_menu_item()
		.get_menu();

	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Paused")
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.with_menu_item("Help", help_menu.get())
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2);  })
		.get_menu();
}

void PauseMenuState::on_load()
{

}

void PauseMenuState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter))
	{
		menu->select();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape))
	{
		menu->back();
	}
}

void PauseMenuState::draw()
{
	menu->render();
}

void PauseMenuState::on_enter()
{

}

void PauseMenuState::on_exit()
{

}
