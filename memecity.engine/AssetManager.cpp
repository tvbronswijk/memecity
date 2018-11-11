﻿#include "AssetManager.h"
#include "GraphicsFacade.h"

///<summary>Constructor which assigns a given graphics_facade to it's member variable.</summary>
AssetManager::AssetManager(GraphicsFacade& graphics_facade) : graphics_facade(graphics_facade)
{
}

///<summary>Cleanup.</summary>
AssetManager::~AssetManager()
{
	/*for (auto texture : textures)
	{
		if (texture.second != nullptr)
		{
			SDL_DestroyTexture(texture.second);
		}
	}*/
//	textures.clear();

	/*for (auto text : texts)
	{
		if (text.second != nullptr)
		{
			SDL_DestroyTexture(text.second);
		}
	}*/
	texts.clear();

	for (auto font : fonts)
	{
		if (font.second != nullptr)
		{
			TTF_CloseFont(font.second);
		}
	}
	fonts.clear();
}

///<summary>Returns a texture based on given filename.</summary>
const RawTextureWrapper& AssetManager::get_texture(std::string filename)
{
	std::string fullPath = base_path;
	fullPath.append("Assets/" + filename);

	if (textures.find(fullPath) == textures.end())
	{
		textures[fullPath] = graphics_facade.load_texture(fullPath);
	}

	return *textures[fullPath];
}

///<summary>Returns a text texture based on a given text and filename.</summary>
const RawTextureWrapper&  AssetManager::get_text(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = get_font(filename, size);
	std::string key = text + filename + char(size) + char(color.r) + char(color.g) + char(color.b);

	if (texts.find(key) == texts.end())
	{
		texts[key] = graphics_facade.load_text_texture(font, text, color);
	}

	return *texts[key];
}

///<summary>Returns a font based on a given filename.</summary>
TTF_Font* AssetManager::get_font(std::string filename, int size)
{
	std::string fullPath = base_path;
	fullPath.append("Assets/" + filename);
	const std::string key = fullPath + char(size);

	if (fonts[key] == nullptr)
	{
		fonts[key] = TTF_OpenFont(fullPath.c_str(), size);

		if (fonts[key] == nullptr)
		{
			printf("Font loading error: Font-%s Error-%s\n", filename.c_str(), TTF_GetError());
		}
	}

	return fonts[key];
}
///<summary>Returns music based on a given filename.</summary>
Mix_Music* AssetManager::get_music(std::string filename)
{
	std::string fullPath = base_path;
	fullPath.append("Assets/" + filename);

	if (music[fullPath] == nullptr)
	{
		music[fullPath] = Mix_LoadMUS(fullPath.c_str());

		if (music[fullPath] == nullptr)
		{
			printf("Music loading error: file- %s Error- %s", filename.c_str(), Mix_GetError());
		}
	}

	return music[fullPath];
}

///<summary>Returns a sound effect based on a given filename.</summary>
Mix_Chunk* AssetManager::get_sfx(std::string filename)
{
	std::string fullPath = base_path;
	fullPath.append("Assets/" + filename);

	if (sfx[fullPath] == nullptr)
	{
		sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (sfx[fullPath] == nullptr)
		{
			printf("SFX loading error: file-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return sfx[fullPath];
}