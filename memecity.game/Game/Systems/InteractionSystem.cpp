#include "InteractionSystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "..\..\Assets.h"

using namespace memecity::engine::ecs;

void InteractionSystem::run(EntityManager &em) const {
	auto vector = em.get_components_of_type<InteractionComponent>();
	for (auto& component : vector) {
		auto text_texture = &component.get().get_texture();
		if (text_texture->get_text() != " ") {
			if (component.get().entity().get<AIComponent>() != nullptr) {
				if (component.get().start_time > 50) {
					auto npc_interaciton_texture = this->_context->get_multimedia_manager().get_text(" ", 14);
					npc_interaciton_texture->set_position({ 0, -35 });
					npc_interaciton_texture->set_parent(text_texture->get_parent());
					component.get().texture = std::move(npc_interaciton_texture);
					component.get().start_time = 0;
				}
			}
			else {
				if (component.get().start_time > 100) {
					component.get().current_text_int++;
					if (component.get().current_text_int < component.get().text.size()) {
						auto npc_interaciton_texture = this->_context->get_multimedia_manager().get_text(component.get().text[component.get().current_text_int], 14);
						
						npc_interaciton_texture->set_position({ 0, -35 });
						npc_interaciton_texture->set_parent(text_texture->get_parent());
						component.get().texture = std::move(npc_interaciton_texture);
						component.get().start_time = 0;
					}
					else {
						auto npc_interaciton_texture = this->_context->get_multimedia_manager().get_text(" ", 14);

						npc_interaciton_texture->set_position({ 0, -35 });
						npc_interaciton_texture->set_parent(text_texture->get_parent());
						component.get().texture = std::move(npc_interaciton_texture);
						component.get().start_time = 0;
						component.get().current_text_int = 0;
					}
				}
			}
			component.get().start_time += _context->get_timer().get_delta_time();
		}
	}
}

void InteractionSystem::on_interact(EntityManager &em, InteractionEventArgs args) {

	auto xy = args.source.get<PositionComponent>();
	auto interaction = args.source.get<InteractionComponent>();

	auto text_texture = &interaction->get_texture();

	std::string text = " ";

	if (args.source.get<AIComponent>() != nullptr) {
		auto health = args.source.get<HealthComponent>();
		if (health->health > 0) {
			text = interaction->text[(rand() % (interaction->text.size()))];
		}
	}
	else {
		if (interaction->get_texture().get_text() != " ") {
			interaction->current_text_int++;
			if (interaction->current_text_int < interaction->text.size()) {
				text = interaction->text[interaction->current_text_int];
			}
			else {
				interaction->current_text_int = 0;
			}
		}else
		text = interaction->text[0];
	}

	auto npc_interaciton_texture = _context->get_multimedia_manager().get_text("Minecraftia-Regular.ttf", text, 14, { 255,255,255 });
	npc_interaciton_texture->set_position({ 0, -35 });
	npc_interaciton_texture->set_parent(text_texture->get_parent());
	interaction->texture = std::move(npc_interaciton_texture);

}
