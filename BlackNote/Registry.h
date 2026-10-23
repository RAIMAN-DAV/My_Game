#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"

 
class Registry {
	Storage stor;        //Хранилище
	friend class Entity;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер
	uint64_t freeCount = 0; //Количество свободных ячеек

	size_t FindFreeSlot() {
		for (size_t i = 0; i < ids.size(); ++i) {
			if (ids[i].CheckFree()) {
				return i;
			}
		}

		return ids.size(); // Свободная ячейка не найдена.
	}

public:
	 
	EntityID& Add() {
		if (freeCount > 0) {
			uint64_t idx = FindFreeSlot();
			if (idx < ids.size()) {
				ids[idx].newID(nextID);
				nextID++;
				freeCount--;

				return ids[idx];
			}
		}

		ids.emplace_back(nextID);
		nextID++;

		return ids.back();
	}

	bool CheckID(const uint64_t ID) {
		if (ID == 0 || ID >= nextID) {
			return true;
		}
		return false;
	}
	bool CheckID(const EntityID& ID) {
		if (ID.PrintID() == 0 || ID.PrintID() >= nextID) {
			return true;
		}
		return false;
	}

	template<typename T, typename... Args>
	void AddComponent(EntityID& ID, Args&&... args) {
		if (CheckID(ID)) {
			cout << "ID " << ID.PrintID() << ": Error. Not Initialized" << endl;
		}
		else stor.AddComponents<T>(ID, forward<Args>(args)...);
	}

	template<typename T>
	T* TryGetComponent(EntityID& ID) {
		if (CheckID(ID)) {
			cout << "ID" << ID.PrintID() << ": Error. Not Initialized" << endl;

			return nullptr;
		}

		T* component = stor.TryGetComponents<T>(ID);
		if (component == nullptr) cout << "ID" << ID.PrintID() << ": Компонент пуст \n";

		return component;
	}

	template<typename... Args>
	bool HasComponent(EntityID& ID) {
		if (CheckID(ID)) {
			cout << "ID" << ID.PrintID() << ": Error. Not Initialized" << endl;

			return false;
		}
		return stor.HasComponent<Args...>(ID);
	}

	void DestroyEntity(EntityID& ID) {
		if (ID.PrintID() == 0) {
			return;
		}
		stor.ResetComponents(ID);
		cout << "ID" << ID.PrintID() << ": Entity Destroy \n ";
		ID.DestroyID();
		freeCount++;
	}

};



