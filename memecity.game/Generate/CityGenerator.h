#ifndef _CITY_GENERATOR_H
#define _CITY_GENERATOR_H
#include <ECS.h>
#include "MultimediaManager.h"
#include "strategy\Strategy.h"

namespace generate {
	class CityGenerator {
	private:
		std::unique_ptr<strategy::Strategy> strategy;
	public:
		CityGenerator() = default;
		
		template<class T, class... Args>
		void set_strategy(Args&&... args)
		{
			static_assert(std::is_convertible<T*, strategy::Strategy*>::value, "Only Generator Strategies can be set.");
			static_assert(std::is_constructible<T, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			strategy = std::make_unique<T>(std::forward<Args>(args)...);
		}

		void generate(int w, int h, ecs::EntityManager& em, MultimediaManager &multimedia_manager) const;
	};
}

#endif