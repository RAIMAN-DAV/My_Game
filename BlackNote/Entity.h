#pragma once
#include "Registry.h"
#include "EntitySystems.h"



class Entity {
	EntityID& ID;
	Registry* registry;
	EntitySystems system;

public:
	Entity(Registry& reg) 
		: ID(reg.Add()), registry(&reg), system(ID, reg) { }


	template<typename T>
	void AddSystem() {
		system.SystemAdd<T>();
	}

	template <typename T, typename... Args>
	void Component(Args... args) {
		registry->AddComponent<T>(ID, args...);
	}


	void Draw(Color color) { 
		if (ID.PrintID() == 0) return;

		Position* pos = registry->TryGetComponent<Position>(ID);
		Dimension* dim = registry->TryGetComponent<Dimension>(ID);

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, color);
		}
	}

	template<typename T>
	void UseSystem() {
		if (ID.PrintID() == 0) return;

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<T>(move_x, move_y);
		}
	}

	template<typename T>
	void DestroySystem() {
		system.DestroySystem<T>();
	}
	void DestroySystem() {
		system.DestroySystem();
	}

	void Destroy() {
		DestroySystem();
		registry->DestroyEntity(ID);
	}

};


