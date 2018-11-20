#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine.h>
#include <ECS.h>
#include "..\Generate.h"

struct GameState : public memecity::engine::state::State {
private:
	memecity::engine::ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;
public:
	GameState(memecity::engine::state::StateMachine& sm)
		: State(sm){}
	void init() override;
	void update(float dt) override;
	void draw() override;
	~GameState() = default;
};

#endif
