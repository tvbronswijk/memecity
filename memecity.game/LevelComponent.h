#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <iostream>
#include <map>

struct LevelComponent : public Component, public Serializable {

	static std::string COMPONENT_TYPE;

public:
	int _level;
	LevelComponent(Entity* e);
	LevelComponent(int _level, Entity* e);
	LevelComponent(int world, int range, Entity* e);
	std::string get_type() override;
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif
