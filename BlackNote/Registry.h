#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"

 
class Registry {
	Storage stor;        //Хранилище
	friend class Entity;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер

public:
	 
	EntityID& Add() {
		ids.emplace_back(nextID);
		nextID++;

		return ids.back();
	}

	template<typename T, typename... Args>
	void AddComponent(uint64_t ID, Args&&... args) {
		if (ID == 0 || ID > ids.size()) {
			cout << "ID " << ID << ": Error. Not Initialized" << endl;
		}
		else stor.AddComponents<T>(ids[ID - 1], forward<Args>(args)...);
	}

	template<typename T>
	T* TryGetComponent(uint64_t ID) {
		if (ID == 0 || ID > ids.size()) {
			cout << "ID" << ID << ": Error. Not Initialized" << endl;

			return nullptr;
		}

		T* component = stor.TryGetComponents<T>(ids[ID - 1]); 
		if (component == nullptr) cout << "ID"  << ID << ": Компонент пуст \n";

		return component;
	}

};



