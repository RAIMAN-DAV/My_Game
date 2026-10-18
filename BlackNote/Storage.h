#pragma once
#include "Components.h"
#include <type_traits>

class Storage {
	vector<Position> pos;
	vector<Dimension> dim;
	vector<HitBox> HB;

	template<typename T>
	vector<T>& GetComponents() {
		if constexpr(is_same_v<T, Position>) {
			return pos;
		} 
		else if constexpr(is_same_v<T, Dimension>) {
			return dim;
		}
		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported component type");
		}
	}
	template<typename T>
	string PrintComponents() {
		if constexpr (is_same_v<T, Position>) return "Position ";

		else if constexpr (is_same_v<T, Dimension>) return "Dimension";

		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported component type");
		}
	}
 

	template<typename T>
	void FindComponents(EntityID& startID, vector<T>& components, T*& result) {
		for (auto& component : components) {
			if (&component.ID == &startID) {
				result = &component;
				return;
			}
		}
		result = nullptr;
	}

public:

	template<typename T, typename... Args>
	void AddComponents(EntityID& ID, Args&&... args) {
		auto& components = GetComponents<T>();

		T* component = nullptr;
		FindComponents(ID, components, component);

		if (component == nullptr) {
			components.emplace_back(ID, forward<Args>(args)...);

			cout << "ID" << ID.PrintID() << ": Success! T.A. "
				<< PrintComponents<T>() << " add.   ";
			components.back().PrintElem();
		}
		else {
			component->Set(forward<Args>(args)...);

			cout << "ID" << ID.PrintID() << ": Success! T.A. "
				<< PrintComponents<T>() << " rebut. ";
			component->PrintElem();
		}
	}

	template<typename T>
	T* TryGetComponents(EntityID& ID) {
		auto& components = GetComponents<T>();
		T* component = nullptr;

		FindComponents(ID, components, component);

		return component;
	}

};
