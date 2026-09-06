#pragma once
#include "ECS_DATA.h"

class EntityID {
	uint64_t ID;

	EntityID(uint64_t startID) 
		: ID(startID) {}
};

