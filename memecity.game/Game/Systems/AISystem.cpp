#include "AISystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
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


std::queue<Point> AISystem::calculate_next_positions(Point start , Point end, std::queue<Point> queue) const{
	float x = 0;
	float y = 0;

	if (start.x < (end.x - range)) { x = 10; }
	else if (start.x >  (end.x + range)) {x = 10 * -1;}
	if (start.y < (end.y - range)) { y = 10; }
	else if(start.y > (end.y + range)) { y = 10 * -1;}

	queue.push(Point(start.x + x, start.y + y));
	queue.push(Point(start.x + x, start.y));
	queue.push(Point(start.x, start.y + y));
	queue.push(Point(start.x - x, start.y - y));

	return queue;
}

bool AISystem::check_player_position_Y(Point location, Point end) const{
	if ((location.y >= end.y - range) && (location.y <= end.y + range)) {
		return true;
	}
	return false;
}

bool AISystem::check_player_position_X(Point location , Point end) const{
	if ((location.x >= end.x - range) && (location.x <= end.x + range)) {
		return true;
	}
	return false;
}


void AISystem::best_first_search(EntityManager& em, const PositionComponent& npc_xy) const{
	auto velocity = npc_xy.entity().get<VelocityComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();

	auto player_position = player_component.entity().get<PositionComponent>();

	Point end(player_position->x, player_position->y); // end location
	Point start(npc_xy.x, npc_xy.y); // start location

	std::vector<Point> path; // path to end location
	std::queue<Point> queue; // need to visited these positions

	queue = calculate_next_positions(start, end, queue);

	while (!queue.empty()) {
		Point location = queue.front();
		queue.pop();
		path.push_back(location);
		if (check_player_position_X(location, end) && check_player_position_Y(location, end)) {
			queue = {};
		}
		else { 
			queue = calculate_next_positions(location, end, queue); 
		}
	}
	auto direction = path.front();
	if (npc_xy.x < direction.x) { 
		if (!check_player_position_X(direction, end)) velocity->x += movement;
	}
	else if(npc_xy.x > direction.x){
		if(!check_player_position_X(direction, end)) velocity->x -= movement;
	}
	if (npc_xy.y > direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y -= movement;
	}
	else if(npc_xy.y < direction.y) {
		if (!check_player_position_Y(direction, end)) velocity->y += movement;
	}
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


	std::cout << "roaming" << "\n";
	std::cout << (int)(ai->direction) << "\n";

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

void AISystem::fleeing(EntityManager& em, const PositionComponent& npc_position) const { 
	auto velocity = npc_position.entity().get<VelocityComponent>();
	auto ai = npc_position.entity().get<AIComponent>();
	auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();
	auto player_position = player_component.entity().get<PositionComponent>();

	if (npc_position.x < player_position->x) { velocity->x -= movement; }
	else if (npc_position.x > player_position->x) { velocity->x += movement; }
	if (npc_position.y < player_position->y) { velocity->y -= movement; }
	else if (npc_position.y > player_position->y) { velocity->y += movement; }

	int distance_x = std::abs((player_position->x - npc_position.x));
	int distance_y = std::abs((player_position->y - npc_position.y));
	
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
			auto xy = element.get().entity().get<PositionComponent>();
			switch (AI->state)
			{
			case State::Fighting:
				best_first_search(em, *xy);
				break;
			case State::Fleeing:
				fleeing(em, *xy);
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
