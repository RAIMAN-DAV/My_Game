#pragma once

#include "Entity.h"


class Pattern {
	EntityID num{ 0 };
	optional<Position> pos;
	optional<Dimension> dim;
	optional<Velocity> vel;
	bool move = false;

	template<typename T>
	optional<T>& GetComponent() {
		if constexpr (is_same_v<T, Position>) {
			return pos;
		}
		else if constexpr (is_same_v<T, Dimension>) {
			return dim;
		}
		else if constexpr (is_same_v<T, Velocity>) {
			return vel;
		}
		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported System type");
		}
	}

	void ApplyTo(Entity& entity) {
		if (pos) {
			entity.Component<Position>(pos->x, pos->y);
		}
		if (dim) {
			entity.Component<Dimension>(dim->width, dim->height);
		}
		if (vel) {
			entity.Component<Velocity>(vel->velocity);
		}
		if (move) {
			entity.AddSystem<MovementSystem>();
		}
	}


public:

	template<typename T, typename... Args>
	void AddPatternComponent(Args... args) {
		if constexpr (is_same_v<T, MovementSystem>) {
			static_assert(sizeof...(Args) == 0,
				"MovementSystem pattern does not accept arguments");
			move = true;
		}
		else {
			auto& component = GetComponent<T>();

			if (!component) {
				component.emplace(num, args...);
			}
			else {
				component->Set(args...);
			}
		}
	}

	void ApplyPattern(Entity& entity) {
		if (entity.IsBound()) {
			entity.Reset();
		}
		else {
			entity.Recreate();
		}
		ApplyTo(entity);
	}

	Pattern& operator>>(Entity& entity) {
		ApplyPattern(entity);
		return *this;
	}

};