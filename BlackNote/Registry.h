#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"

 
class Registry {
	Storage stor;
	friend class Entity;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер

	void AddPosition(EntityID& ID, float x, float y) {
		stor.addPos(ID, x, y);
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


};



