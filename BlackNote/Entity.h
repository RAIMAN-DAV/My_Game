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
		registry->AddComponent<T>(ID.PrintID(), args...);
	}


	void Draw(Color color) { 
		Position* pos = registry->TryGetComponent<Position>(ID.PrintID());
		Dimension* dim = registry->TryGetComponent<Dimension>(ID.PrintID());

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, color);
		}
	}

	template<typename T>
	void UseSystem() {; 

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<T>(move_x, move_y);
		}
	}
};


