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

	bool CheckID(uint64_t ID) {
		if (ID == 0 || ID > ids.size()) {
			return true;
		}
		return false;
	}

	template<typename T, typename... Args>
	void AddComponent(uint64_t ID, Args&&... args) {
		if (CheckID(ID)) {
			cout << "ID " << ID << ": Error. Not Initialized" << endl;
		}
		else stor.AddComponents<T>(ids[ID - 1], forward<Args>(args)...);
	}

	template<typename T>
	T* TryGetComponent(uint64_t ID) {
		if (CheckID(ID)) {
			cout << "ID" << ID << ": Error. Not Initialized" << endl;

			return nullptr;
		}

		T* component = stor.TryGetComponents<T>(ids[ID - 1]); 
		if (component == nullptr) cout << "ID"  << ID << ": Компонент пуст \n";

		return component;
	}

	template<typename... Args>
	bool HasComponent(uint64_t ID) {
		if (CheckID(ID)) {
			cout << "ID" << ID << ": Error. Not Initialized" << endl;

			return false;
		}
		return stor.HasComponent<Args...>(ids[ID - 1]);
	}
};



