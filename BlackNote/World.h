#pragma once

#include "Pattern.h"
#include <memory>


class World {
	Registry* registry;

	vector < std::unique_ptr <Entity> > entities;

	uint64_t freeCount = 0;
	uint64_t Count = 0;

public:


	// explicit - запрещает неявное преобразование аргумента
	explicit World(Registry& reg)
		: registry(&reg) {
	}

	~World() = default;

	Entity& Add() {
		auto entity = std::make_unique<Entity>(*registry);
		entities.push_back(std::move(entity));

		return *entities.back();
	 }

	template<typename Function>
	void ForEach(Function&& action) {
		for (auto& entity : entities) {
			if (entity->IsBound()) {
				action(*entity);
			}
		}
	}

	template<typename... Args, typename Function, typename... Extra>
	void ForEach(Function&& action, Extra&&... extra) {
		for (auto& entity : entities) {
			if (!entity->IsActive()) continue;

			// Собираем optional-кортежи для всех запрошенных компонентов.
			auto results = std::make_tuple(
				entity->GetElemsComponent<Args>()...
			);

			std::apply(

				[&action, &extra...](const auto&... components) {
					// Если хотя бы одного компонента нет — пропускаем вызов.
					if (!(components.has_value() && ...)) return;

					auto values = std::tuple_cat(
						*components...,
						std::make_tuple(extra...)
					);

					std::apply(action, values);
				},
				results);
		}
	}

	World(const World&) = delete;
	World& operator=(const World&) = delete;
};
