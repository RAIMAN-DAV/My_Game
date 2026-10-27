#pragma once
#include "Registry.h"
#include "EntitySystems.h"



class Entity {
	EntityID* ID;
	Registry* registry;
	EntitySystems system;


public:
	Entity(Registry& reg)
		: ID(&reg.Add()), registry(&reg), system(*ID, reg) {
	}

	~Entity() {
		Destroy();
	}

	//Добавление систем
	template<typename T>
	void AddSystem() {
		if (ID == nullptr) return;

		system.SystemAdd<T>();
	}

	//Добавление компонента через реестр
	template <typename T, typename... Args>
	void Component(Args... args) {
		if (ID == nullptr || ID->PrintID() == 0) return;

		registry->AddComponent<T>(*ID, args...);
	}

	//Вывод на экран объекта через RayLib
	void Draw(Color color) {
		if (ID == nullptr || ID->PrintID() == 0) return;

		Position* pos = registry->TryGetComponent<Position>(*ID);
		Dimension* dim = registry->TryGetComponent<Dimension>(*ID);

		if (pos != nullptr && dim != nullptr) {
			DrawRectangle(pos->x, pos->y, dim->width, dim->height, color);
		}
	}

	//Использование систем
	template<typename T>
	void UseSystem() {
		if (ID == nullptr || ID->PrintID() == 0) return;

		int move_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int move_y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		if (move_x != 0 || move_y != 0) {
			system.UsingSystem<T>(move_x, move_y);
		}
	}

	//Применение шаблона
	void ApplyPattern();


	//Удаление систем
	template<typename T>
	void DestroySystem() {
		if (ID == nullptr) return;

		system.DestroySystem<T>();
	}
	void DestroySystem() {
		if (ID == nullptr) return;

		system.DestroySystem();
	}

	//Очистка сущности
	void Reset() {
		if (ID == nullptr) return;

		DestroySystem();
		registry->ResetEntity(*ID);
	}

	//Удаление сущности
	void Destroy() {
		if (ID == nullptr) return;

		system.Destroy();
		registry->DestroyEntity(*ID);

		ID = nullptr;
	}
	void Recreate() {
		if (ID != nullptr) Destroy();

		ID = &registry->Add();

		system.Recreate(*ID);
	}

	bool IsBound() const {
		return ID != nullptr;
	}

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

};
