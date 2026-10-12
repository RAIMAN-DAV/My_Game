#pragma once
#include "EntityID.h"
#include <iostream>

struct Position {
	EntityID& ID;
	float x, y;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {

		cout << "ID:" << ID.PrintID() << " Success! Position add.   "
			<< "[x, y] = [" << x << ", " << y << "]\n";
	}
	void Set(float start_x, float start_y) {
		x = start_x;
		y = start_y;
	}

	float Get_elem_1() {
		return x;
	}
	float Get_elem_2() {
		return y;
	}
};

struct Dimension {
	EntityID& ID;
	float width; float height;

	Dimension(EntityID& startID, float startWidth, float startHeight) 
		: ID(startID), width(startWidth), height(startHeight) {

		cout << "ID:" << ID.PrintID() << " Success! Dimension add.  "
			<< "[x, y] = [" << width << ", " << height << "]\n";
	}

	void Set(float start_width, float start_height) {
		width = start_width;
		height = start_height;
	}
	
	float Get_elem_1() {
		return width;
	}
	float Get_elem_2() {
		return height;
	}
};


struct HitBox {
	EntityID ID;
	float x, y;
	float width; float height;
};

