#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"

 
class Registry {
	Storage stor;        //Хранилище
	friend class Entity;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер

	void AddPosition(EntityID& ID, float x, float y) {
		stor.addPos(ID, x, y);
	}
	void AddDimension(EntityID& ID, float x, float y) {
		stor.addDim(ID, x, y);
	}

public:
	 
	EntityID& Add() {
		ids.emplace_back(nextID);
		nextID++;

		return ids.back();
	}


	void AddPosition(uint64_t ID, float x, float y) {
		if (ID == 0 || ID > ids.size()) {
			cout << "Error ID: " << ID << endl;
		}
		else stor.addPos(ids[ID - 1], x, y); 	
	}
	void AddDimension(uint64_t ID, float width, float height)  {
		if (ID == 0 || ID > ids.size()) {
			cout << "Error ID: " << ID << endl;
		}
		else stor.addDim(ids[ID - 1], width, height);
	}

	template<typename T>
	void AddComponent(uint64_t ID, float Element_1, float Element_2) {
		if (ID == 0 || ID > ids.size()) {
			cout << "Error ID: " << ID << endl;
		}
		else stor.AddComponents<T>(ids[ID - 1], Element_1, Element_2);
	}
};



