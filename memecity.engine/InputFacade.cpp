﻿#include "InputFacade.h"

/**
 * Updates the Keyboard State to find out which keys are pressed
 */
void InputFacade::update()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) { quit_pressed = true; }
		state = SDL_GetKeyboardState(nullptr);

		switch (event.type)
		{
		case SDL_KEYDOWN:
			std::cout << "you have pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
			break;
		case SDL_KEYUP:
			std::cout << "you have released: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
			break;
		default: 
			break;
		}
	}
}

/**
 * Returns if a given key is pressed
 */
bool InputFacade::is_pressed(InputKeys key) const
{
	return state[key] != 0;
}

/**
 * Returns whether quit is pressed 
 */
bool InputFacade::is_quit_pressed() const
{
	return quit_pressed;
}
