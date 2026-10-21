#pragma once

#include "System_Component.h"
#include <type_traits>


class System {
	Registry* registry;

	vector<MovementSystem> move_s;

	template <typename T>
	vector<T>& GetSystem() {
		if constexpr (is_same_v<T, MovementSystem>) return move_s;

		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported System type");
		}

	}
	template <typename T>
	bool CheckComponent(uint64_t ID) {
		if constexpr (is_same_v<T, MovementSystem>) {
			return registry -> HasComponent<Position, Velocity>(ID);
		}
		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported System type");
		}

	}


	template <typename T>
	void FindSystem(uint64_t ID, vector<T>& systems, T*& result) {
		for (auto& system : systems) {
			if (system.ID == ID) {
				result = &system;
				return;
			}
		}
		result = nullptr;
	}

public:
	System(Registry& reg): registry(&reg){}

	template <typename T>
	void SystemAdd(uint64_t ID) {
		if (registry -> CheckID(ID)) {
			cout << "ID" << ID << ": Error. Not Initialized" << endl;

			return;
		}

		auto& systems = GetSystem<T>();

		T* system = nullptr;
		FindSystem(ID, systems, system);

		if (system != nullptr) {
			cout << "ID" << ID << ": Error. Double system \n";
			return;
		}
		else {
			if (CheckComponent<T>(ID)) {
				systems.emplace_back(ID, *registry);

				systems.back().Print_Add();
			}
			else {
				cout << "ID" << ID << ": Error. The components are not initialized. \n";
			}
		}
	}


	template <typename T, typename... Args>
	void UsingSystem(uint64_t ID, Args... args) {
		if (registry->CheckID(ID)) {
			cout << "ID" << ID << ": Error. Not Initialized" << endl;

			return;
		}

		auto& systems = GetSystem<T>();

		T* system = nullptr;
		FindSystem(ID, systems, system);

		if (system == nullptr) {
			cout << "ID" << ID << ": Error. Dont used System. \n";
			return;
		}
		system -> UsingSystem(args...);
	}

};

