#pragma once
#include "ECS_DATA.h"

class EntityID {
	uint64_t ID;
public:
	EntityID(uint64_t startID) 
		: ID(startID) {}

	uint64_t PrintID() {
		return ID;
	}
};

