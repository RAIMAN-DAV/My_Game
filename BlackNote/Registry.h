#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"
 
class Registry {
	Storage stor;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер

public:
	EntityID& Add() {
		ids.emplace_back(nextID);
		nextID++;

		return ids.back();
	}
	void AddPosition(uint64_t ID, float x, float y) {
		EntityID& entityRef = ids[ID - 1];
		stor.addPos(entityRef, x, y);
	}

};



