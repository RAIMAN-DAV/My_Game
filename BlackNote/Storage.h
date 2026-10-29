#pragma once
#include "Components.h"
#include <type_traits>

class Storage {
	vector<Position> pos;
	vector<Dimension> dim;
	vector<Velocity> vel;
	vector<HitBox> HB;

	template<typename T>
	vector<T>& GetComponents() {
		if constexpr(is_same_v<T, Position>) {
			return pos;
		} 
		else if constexpr(is_same_v<T, Dimension>) {
			return dim;
		}
		else if constexpr (is_same_v<T, Velocity>) {
			return vel;
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

		else if constexpr (is_same_v<T, Velocity>) return "Velocity";

		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported component type");
		}
	}
 

	//Поиск компонента 
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

	//Добавление компонента
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

	// Возвращает указатель на компонент типа T указанной сущности.
	template<typename T>
	T* TryGetComponents(EntityID& ID) {
		auto& components = GetComponents<T>();
		T* component = nullptr;

		FindComponents(ID, components, component);

		return component;
	}

	//Проверка наличия компонента
	template<typename... Args>
	bool HasComponent(EntityID& ID) {
		return ((TryGetComponents<Args>(ID) != nullptr) && ...);
	}

	//Сброс данных компонентов
	void ResetComponents(EntityID& ID) {
		Position* pos = TryGetComponents<Position>(ID);
		if (pos != nullptr) pos->Reset();

		Dimension* dim = TryGetComponents<Dimension>(ID);
		if (dim != nullptr) dim->Reset();

		Velocity* vel = TryGetComponents<Velocity>(ID);
		if (vel != nullptr) vel->Reset();

	}

	template<typename T>
	auto GetElemsComponent(EntityID& ID) {
		auto* component = TryGetComponents<T>(ID);

		using Elems = decltype(component->GetElems());

		if (component == nullptr)
			return std::optional<Elems>{};

		return std::optional<Elems>{component->GetElems()};
	}
	/* Или можно: 
	 template<typename T>
	 auto GetElemsComponent(EntityID& ID) {
     auto* component = TryGetComponents<T>(ID);

     return component
         ? std::optional{component->GetElems()}
         : std::nullopt;
	}
	*/
};
