#include "AISystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <stack>
#include "../Enum/AIStates.h"
using namespace memecity::engine::ecs;


bool AISystem::check_health(const Entity& entity) const{
	auto AI = entity.get<AIComponent>();
	auto health = entity.get<HealthComponent>();
	if(health->health <= 0) {
		return false;
	}
	return true;
}

Point AISystem::calculate_next_route(Point start , Point end, int speed) const{
	float x = 0;
	float y = 0;

	if (start.x <= (end.x - range)) { x = 10; }
	else if (start.x >=  (end.x + range)) {x = 10 * -1;}
	if (start.y <= (end.y - range)) { y = 10; }
	else if(start.y >= (end.y + range)) { y = 10 * -1;}

	return Point(x, y);
}

bool AISystem::check_player_position(Point location, Point end) const{
	if ((location.y >= end.y - range) && (location.y <= end.y + range)) {
		if ((location.x >= end.x - range) && (location.x <= end.x + range)) {
			return true;
		}
	}
	return false;
}

void AISystem::point_jump_search(EntityManager& em, const BaseComponent& npc_base) const{
	auto velocity = npc_base.entity().get<VelocityComponent>();
	auto player_base = em.get_components_of_type<PlayerComponent>()[0].get().entity().get<BaseComponent>();

	bool next = false;

	std::vector<Point> path; // path to end location
	std::stack<Point> stack; // need to visited these positions

	Point start(npc_base.location.x, npc_base.location.y);
	Point end(player_base->location.x, player_base->location.y);

	Point direction = calculate_next_route(start, end, 10);

	stack.push(Point((npc_base.location.x), (npc_base.location.y + range)));
	stack.push(Point((npc_base.location.x +range), (npc_base.location.y)));
	stack.push(Point((npc_base.location.x), (npc_base.location.y - range)));
	stack.push(Point((npc_base.location.x - range), (npc_base.location.y)));
	stack.push(Point((npc_base.location.x + direction.x), (npc_base.location.y + direction.y)));

	while (!stack.empty()) {
		Point node = stack.top();
		Point next_position(node);
		stack.pop();
		direction = calculate_next_route(node, end, 10);
		int counter = 1;
		next = false;
		while(!next){
			next_position = Point(node.x + (direction.x * counter), node.y + (direction.y * counter));
			Point new_direction = calculate_next_route(next_position, end, 10);
			if(direction.x != new_direction.x || direction.y != new_direction.y){
				stack.push(next_position);
				path.emplace_back(next_position);
				//counter = 1;
				direction = new_direction;
				next = true;
			}else {
				counter++;
			}
			if (check_player_position(next_position, end)) {
				path.emplace_back(node);
				while (!stack.empty()) stack.pop();
				next = true;
			}
		}
	}
	auto movement = npc_base.entity().get<AIComponent>()->movement_speed;
	auto next_step = path.front();
	direction = calculate_next_route(start, next_step, movement);
	if (direction.x > 0) velocity->x = movement;
	else if(direction.x < 0) velocity->x = (movement * -1);
	if (direction.y > 0) velocity->y = movement;
	else if(direction.y < 0) velocity->y = (movement * -1);
}

void AISystem::move_random(const Entity& entity) const{
	auto velocity = entity.get<VelocityComponent>();
	auto ai = entity.get<AIComponent>();

	auto random = (rand() % 5000);

	if (random < 1) {
		auto direction = (rand() % 4);
		switch (direction)
		{
		case 0:
			ai->direction = AIComponent::Direction::Down;
			break;
		case 1:
			ai->direction = AIComponent::Direction::Up;
			break;
		case 2:
			ai->direction = AIComponent::Direction::Left;
			break;
		case 3:
			ai->direction = AIComponent::Direction::Right;
			break;
		case 4:
			ai->direction = AIComponent::Direction::Idle;
			break;

		}
	}

	auto movement = entity.get<AIComponent>()->movement_speed;
	switch (ai->direction) {
	case AIComponent::Direction::Down:
		velocity->y -= movement;
		break;
	case AIComponent::Direction::Up:
		velocity->y += movement;
		break;
	case AIComponent::Direction::Left:
		velocity->x -= movement;
		break;
	case AIComponent::Direction::Right:
		velocity->x += movement;
		break;
	case AIComponent::Direction::Idle:
		break;
	}

}

void AISystem::fleeing(EntityManager& em, const BaseComponent& npc_base) const { 
	auto velocity = npc_base.entity().get<VelocityComponent>();
	auto ai = npc_base.entity().get<AIComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();
	auto player_position = player_component.entity().get<BaseComponent>();
	auto movement = ai->movement_speed;

	if (npc_base.location.x < player_position->location.x) { velocity->x -= movement; }
	else if (npc_base.location.x > player_position->location.x) { velocity->x += movement; }
	if (npc_base.location.y < player_position->location.y) { velocity->y -= movement; }
	else if (npc_base.location.y > player_position->location.y) { velocity->y += movement; }

	int distance_x = std::abs((player_position->location.x - npc_base.location.x));
	int distance_y = std::abs((player_position->location.y - npc_base.location.y));
	
	int absolute_distance = std::sqrt((distance_x * distance_x) + (distance_y * distance_y));
	if (absolute_distance > 1000) {
		ai->state = State::Roaming;
	}
}

void AISystem::run(EntityManager& em) const {
	auto vector = em.get_components_of_type<AIComponent>();
	auto player = em.get_entities_with_component<PlayerComponent>()[0];

	for (auto& element : vector) {
		if (check_health(element.get().entity())) {
			auto AI = element.get().entity().get<AIComponent>();
			auto base = element.get().entity().get<BaseComponent>();
			switch (AI->state)
			{
			case State::Fighting:
				point_jump_search(em, *base);
				break;
			case State::Fleeing:
				fleeing(em, *base);
				break;
			case State::Roaming:
				move_random(element.get().entity());
				break;
			case State::Idle:
				break;
			default:
				break;
			}
		}
	}
}
