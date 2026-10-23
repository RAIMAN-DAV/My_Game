#pragma once
#include "ECS_DATA.h"

class EntityID {
	uint64_t ID;
public:
	EntityID(uint64_t startID) 
		: ID(startID) {}

	uint64_t PrintID() const{
		return ID;
	}

	void DestroyID() {
		ID = 0;
	}
	void newID(uint64_t id) {
		if(ID == 0 && id != 0) {
			ID = id;
		}
	}
	bool CheckFree() const{
		return ID == 0;
	}

	bool operator==(const EntityID& other) const {
		return ID == other.ID;
	}
};

