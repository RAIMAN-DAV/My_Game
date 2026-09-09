#pragma once
#include "EntityID.h"
#include <iostream>

struct Position {
	EntityID& ID;
	float x, y;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {

		cout << "ID:" << ID.PrintID() << " Success! Position add. "
			<< "[x, y] = [" << x << ", " << y << "]\n";
	}
};

struct Dimension {
	EntityID& ID;
	float width; float height;

	Dimension(EntityID& startID, float startWidth, float startHeight) 
		: ID(startID), width(startWidth), height(startHeight) {

		cout << "ID:" << ID.PrintID() << " Success! Dimension add. "
			<< "[x, y] = [" << width << ", " << height << "]\n";
	}
};


struct HitBox {
	float x, y;
	float width; float height;


};