#pragma once

#include "Registry.h"
#include "Components.h"

struct MovementSystem {
	EntityID& ID;
	Registry* registry;

	MovementSystem(EntityID& startID, Registry& reg) : ID(startID), registry(&reg) {}

	void Print_Add() {
		cout << "ID" << ID.PrintID() << ": Success! MovementSystem Add \n";
	}


	void UsingSystem_X(float arg_x) {
		Position* Pos = registry->TryGetComponent<Position>(ID);
		Velocity* Vel = registry->TryGetComponent<Velocity>(ID);

		if (Pos == nullptr || Vel == nullptr) {
			return;
		}

		Pos->x += Vel->velocity * arg_x;

	}
	void UsingSystem_Y(float arg_y) {

		Position* Pos = registry->TryGetComponent<Position>(ID);
		const Velocity* Vel = registry->TryGetComponent<Velocity>(ID);

		if (Pos == nullptr || Vel == nullptr) {
			return;
		}
		Pos->y += Vel->velocity * arg_y;

	}
	void UsingSystem_XY(float arg_x, float arg_y) {

		Position* Pos = registry->TryGetComponent<Position>(ID);
		const Velocity* Vel = registry->TryGetComponent<Velocity>(ID);

		if (Pos == nullptr || Vel == nullptr) {
			return;
		}

		Pos->x += Vel->velocity * arg_x * 0.7f;
		Pos->y += Vel->velocity * arg_y * 0.7f;

	}

	void UsingSystem(float arg_x, float arg_y) {

		if (arg_x == 0 && arg_y == 0) {
			cout << "ID" << ID.PrintID() << ": No changes. Position unchanged.\n";
		}
		else if(arg_x != 0 && arg_y != 0) {
			UsingSystem_XY(arg_x, arg_y);
		}
		else if (arg_x != 0) {
			UsingSystem_X(arg_x);
		}
		else if (arg_y != 0) {
			UsingSystem_Y(arg_y);
		}
	}

};