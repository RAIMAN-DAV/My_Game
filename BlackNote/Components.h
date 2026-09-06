#pragma once
#include "EntityID.h"

struct Position {
	EntityID ID;
	float x, y;
};

struct Dimension {
	float width; float height;


};


struct HitBox {
	float x, y;
	float width; float height;


};