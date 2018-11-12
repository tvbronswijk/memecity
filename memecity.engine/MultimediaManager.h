#ifndef _MULTIMEDIAMANAGER_H
#define _MULTIMEDIAMANAGER_H
#include <memory>
#include "AssetManager.h"
#include "AudioFacade.h"
#include "AnimatedTexture.h"

class Color;
class TextTexture;
class Texture;

class MultimediaManager
{
private:
	std::unique_ptr<AssetManager> asset_manager;
	std::unique_ptr<AudioFacade> audio_facade;
	std::unique_ptr<GraphicsFacade> graphics_facade;

public:
	MultimediaManager(bool is_fullscreen);
	MultimediaManager(std::unique_ptr<AssetManager> asset_manager, std::unique_ptr<AudioFacade> audio_facade, std::unique_ptr<GraphicsFacade> graphics_facade)
		: asset_manager(std::move(asset_manager)), audio_facade(std::move(audio_facade)), graphics_facade(std::move(graphics_facade)) {}
	bool init() const;

	void play_background_music(std::string name, int volume) const;
	void play_sound_effect(std::string name, int repeats, int volume, int channel) const;
	void pause_background_music() const;

	void clear_graphics() const;
	void render_texture(Texture &texture) const;
	void render_text_texture(TextTexture &texture) const;
	void render_graphics() const;

	std::unique_ptr<Texture> get_texture(std::string filename) const;
	std::unique_ptr<Texture> get_texture(std::string filename, int x, int y, int width, int height) const;
	std::unique_ptr<AnimatedTexture> get_animated_texture(TimerFacade &timer, std::string filename, int x, int y, int width, int height, int frame_count, float animation_speed, AnimatedTexture::AnimationDirection direction) const;
	std::unique_ptr<TextTexture> get_text_texture(std::string text, std::string font_path, int size, Color color) const;

	int get_screen_width() const;
	int get_screen_height() const;
};

#endif