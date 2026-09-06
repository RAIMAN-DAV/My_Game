#pragma once
#include "EntityID.h"

struct Position {
	EntityID ID;
	float x, y;

	Position(EntityID startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {}
};

struct Dimension {
	float width; float height;


};


struct HitBox {
	float x, y;
	float width; float height;


};