#ifndef _MEME_ENGINE_H
#define _MEME_ENGINE_H

#include <functional>
#include <iostream>
#include <thread>
#include "Engine\InputManager.h"
#include "Engine\MultimediaManager.h"
#include "Engine\StorageManager.h"

namespace memecity::engine {
	namespace sdl {
		class TimerFacade;
	};

	enum class Threading {
		///<summary>[EXPERIMENTAL]</summary>
		multithreaded,
		singlethreaded
	};

	class MemeEngine
	{
		template<class T>
		using Runnable = std::function<T(MemeEngine&)>;
	private:
		Runnable<int> _runnable;
	protected:
		struct Context
		{
		private:
			MultimediaManager* multimedia_manager;
			InputManager* input_manager;
			sdl::TimerFacade* timer;
			MemeEngine* engine;

		public:
			Context(MultimediaManager& mm, InputManager& im, sdl::TimerFacade& t, MemeEngine& engine)
				: multimedia_manager(&mm), input_manager(&im), timer(&t), engine(&engine) {}
			Context(MemeEngine& engine)
				: multimedia_manager(&engine.multimedia_manager), input_manager(&engine.input_manager), timer(&engine.timer),engine(&engine) {}
			virtual ~Context() = default;

			MultimediaManager& get_multimedia_manager() { return *multimedia_manager; }
			InputManager& get_input_manager() { return *input_manager; }
			sdl::TimerFacade& get_timer() { return *timer; }
			MemeEngine& get_engine() { return *engine; }
		};

		StorageManager storage_manager;
		MultimediaManager multimedia_manager;
		InputManager input_manager;
		sdl::TimerFacade timer;
		std::unique_ptr<Context> _context;

		bool get_fps_trigger = false;
		bool display_game_speed = false;

		using fps_subscriber = std::function<void(bool enabled,int fps)>;
		using game_speed_subscriber = std::function<void(bool enabled, float fps)>;

		std::vector<fps_subscriber> fps_subscribers;
		std::vector<game_speed_subscriber> game_speed_subscribers;

		float game_speed_modifier = 1.0f;

	public:

		void set_games_speed_modifier(float new_speed)
		{
			this->game_speed_modifier = new_speed;
			if (display_game_speed) {
				for (auto& subscriber : game_speed_subscribers) {
					subscriber(true, new_speed);
				}
			}
		}

		float get_game_speed_modifier()
		{
			return this->game_speed_modifier;
		}

		void bind_fps(fps_subscriber s) { fps_subscribers.push_back(s); }
		void bind_game_speed(game_speed_subscriber s) { game_speed_subscribers.push_back(s); }
		void set_display_gamespeed(bool state)
		{
			if (!state) {
				for (auto& subscriber : game_speed_subscribers) {
					subscriber(false, 0.0f);
				}
			}
			display_game_speed = state;
		}
		void set_calculate_fps(bool state)
		{
			if (!state) {
				for (auto& subscriber : fps_subscribers) {
					subscriber(false, 0);
				}
			}
			get_fps_trigger = state;
		}
		MemeEngine() : storage_manager(), multimedia_manager(false), input_manager(), timer() {
			_context = std::make_unique<Context>(*this);
		};

		~MemeEngine() = default;
		///<summary>Start the game. Optional Threading flag allows you to choose between multithreaded and singlethreaded runner. Defaults to singlethreaded.</summary>
		int run(Threading flag = Threading::singlethreaded);
		///<summary>Start the game. Custom runner.</summary>
		int run(Runnable<int> runnable);
		///<summary>Set one of the default runners. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Threading flag);
		///<summary>Set to a custom runner. To be used for runtime switching of runner.</summary>
		virtual void set_runnable(Runnable<int> runnable);

		///<summary>Initialization logic</summary>
		virtual void init() = 0;
		///<summary>Update game logic and handle user input</summary>
		virtual void update(float dt) = 0;
		///<summary>Render textures</summary>
		virtual void draw() = 0;

		virtual Context& get_context() { return *_context; }

		friend int multithreaded(memecity::engine::MemeEngine& engine);
		friend int singlethreaded(memecity::engine::MemeEngine& engine);
	};
}

#endif
