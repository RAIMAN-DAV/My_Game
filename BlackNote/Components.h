#pragma once
#include "EntityID.h"
#include <iostream>

struct Position {
	EntityID& ID;
	float x, y;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {
		cout << ID.PrintID() <<" success!. " 
			<< "[x, y] = [" << x << ", " << y << "]";
	}
};

struct Dimension {
	float width; float height;


};


struct HitBox {
	float x, y;
	float width; float height;


};