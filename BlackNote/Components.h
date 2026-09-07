#pragma once
#include "EntityID.h"
#include <iostream>

struct Position {
	EntityID& ID;
	float x, y;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {

		cout << "ID:" << ID.PrintID() << " Success!. "
			<< "[x, y] = [" << x << ", " << y << "]\n";
	}
};

struct Dimension {
	float width; float height;


};


struct HitBox {
	float x, y;
	float width; float height;


};