﻿#include "MenuState.h"
#include "GameState.h"
#include <UI.h>

using namespace memecity::engine::ui::menu;

void MenuState::init()
{
	auto& multimedia_manager = _context.multimedia_manager;
	auto& input_manager = _context.input_manager;

	auto enable_fullscreen = [&](MenuItem& menu_item) { multimedia_manager.set_fullscreen(true); };
	auto disable_fullscreen = [&](MenuItem& menu_item) { multimedia_manager.set_fullscreen(false); };

	advanced_graphics_menu = MenuBuilder(multimedia_manager)
		.create_menu("Advanced Graphics")
		.with_back_menu_item()
		.get_menu();

	settings_menu = MenuBuilder(multimedia_manager)
		.create_menu("Settings")
		.with_menu_item("Enable fullscreen", nullptr, enable_fullscreen)
		.with_menu_item("Disable fullscreen", nullptr, disable_fullscreen)
		.with_menu_item("Advanced Graphics", advanced_graphics_menu.get())
		.with_back_menu_item()
		.get_menu();

	auto start_game = [&](MenuItem& menu_item) { left_state = true; _state_machine.create_state<GameState>(_context); };
	auto exit = [&](MenuItem& menu_item) {input_manager.quit(); };

	menu = MenuBuilder(multimedia_manager)
		.create_menu("MemeCity")
		.with_menu_item("Start Game", nullptr, start_game)
		.with_menu_item("Settings", settings_menu.get())
		.with_menu_item("Exit", nullptr, exit)
		.get_menu();
}

void MenuState::update(float dt)
{
	if (left_state)
	{
		left_state = false;
		_context.multimedia_manager.play_background_music("bgm-menu.mp3", 100);
	}
}

void MenuState::draw()
{
	menu->render();

	auto& input_manager = _context.input_manager;
	input_manager.update();
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->next();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->previous();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->select();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->back();
	}
	else
	{
		debounce_counter--;
		if (debounce_counter < 0)
		{
			debounce_counter = 0;
		}
	}
}