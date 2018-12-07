#ifndef _GAME_ASSETS_H
#define _GAME_ASSETS_H

namespace assets {
	using Asset = const char*;
	namespace fonts {
		constexpr inline Asset DEFAULT_FONT = "Fonts/Minecraftia-Regular.ttf";
	}
	namespace music {
		constexpr inline Asset DEFAULT_BGM = "Music/bgm-game.mp3";
		constexpr inline Asset MAIN_MENU_BGM = "Music/bgm-menu.mp3";
	}
	namespace sprites {
		namespace tiles {
			constexpr inline Asset GRASS = "Sprites/Tiles/green.bmp";
			constexpr inline Asset ROAD = "Sprites/Tiles/gray.bmp";
			constexpr inline Asset WALL = "Sprites/Tiles/brown.bmp";
			constexpr inline Asset WATER = "Sprites/Tiles/blue.bmp";
		}
		constexpr inline Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
	}
	namespace spritesheets {
		constexpr inline Asset HUMAN_MALE_1 = "Spritesheets/SpriteSheet.png";
	}
};

#endif
