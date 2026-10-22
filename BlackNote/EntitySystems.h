#pragma once

#include "System_Component.h"

//Изучить для проверки коректности введенного 
#include <stdexcept>

//Библиотека для позжего инициализирования объекта 
#include <optional>

class EntitySystems {

	EntityID& ID;
	Registry* registry;

	optional<MovementSystem> move_s;

	template <typename T>
	optional<T>& GetSystem() {
		if constexpr (is_same_v<T, MovementSystem>) return move_s;

		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported System type");
		}

	}
	template <typename T>
	bool CheckComponent() {
		if constexpr (is_same_v<T, MovementSystem>) {
			return registry->HasComponent<Position, Velocity>(ID.PrintID());
		}
		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported System type");
		}

	}


public: 
	EntitySystems(EntityID& id, Registry& reg)
		: ID(id), registry(&reg) { 

		if (reg.CheckID(id.PrintID())) {
			throw invalid_argument("EntitySystems: invalid entity ID \n");
		}
	}


	template <typename T>
	void SystemAdd() {
		if (registry->CheckID(ID.PrintID())) {
			cout << "ID" << ID.PrintID() << ": Error. Not Initialized" << endl;

			return;
		}

		auto& system = GetSystem<T>();

		if (system) {
			cout << "ID" << ID.PrintID() << ": Error. Double system \n";
			return;
		}

		if (CheckComponent<T>()) {
			system.emplace(ID.PrintID(), *registry);

			system->Print_Add();
		}
		else {
			cout << "ID" << ID.PrintID() << ": Error. The components are not initialized. \n";
		}
	}

	template <typename T, typename... Args>
	void UsingSystem(Args... args) {
		if (registry->CheckID(ID.PrintID())) {
			cout << "ID" << ID.PrintID() << ": Error. Not Initialized" << endl;

			return;
		}

		auto& system = GetSystem<T>();

		if (!system) {
			cout << "ID" << ID.PrintID() << ": Error. Dont used EntitySystem. \n";
			return;
		}
		system ->UsingSystem(args...);

	}
};
