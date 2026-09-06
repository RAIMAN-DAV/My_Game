#pragma once
#include "ECS_DATA.h"
#include "Storage.h"
#include "EntityID.h"

class Registry {
	storage stor;
	EntityID ID;

	deque<EntityID> ids; // Контейнер с ID
	uint64_t nextID = 1; // Следующий выдаваемый номер

public:
	EntityID& Add() {
		ids.emplace_back(nextID);
		nextID++;

		return ids.back();
		}


};



