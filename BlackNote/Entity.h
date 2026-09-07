#pragma once
#include "Registry.h"



class Entity {
	EntityID& ID;
	Registry* registry;

public:
	Entity(Registry& reg) 
		: ID(reg.Add()), registry(&reg) { }

	void Position(float x, float y);
};


