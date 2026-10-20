#pragma once
#include "EntityID.h"
#include <iostream>

struct Position {
	EntityID& ID;
	float x, y;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {}

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

	void PrintElem() {
		cout << "[x, y] = [" 
			<< x
			<< ", " 
			<< y 
			<< "] \n";
	}
};

struct Dimension {
	EntityID& ID;
	float width; float height;

	Dimension(EntityID& startID, float startWidth, float startHeight) 
		: ID(startID), width(startWidth), height(startHeight) {	}

	void Set(float start_width, float start_height) {
		width = start_width;
		height = start_height;
	}
	
	const float Get_elem_1() {
		return width;
	}
	const float Get_elem_2() {
		return height;
	}

	const void PrintElem() {
		cout << "[w, h] = ["
			<< width
			<< ", "
			<< height 
			<< "] \n";
	}
};

struct Velocity {
	EntityID& ID;
	float velocity;

	Velocity(EntityID& startID, float startVelosity) 
		: ID(startID), velocity(startVelosity){}

	void Set(float startVelosity) {
		velocity = startVelosity;
	}

	const void PrintElem() {
		cout << " Velocity = ["
			<< velocity
			<< "] \n";
	}

};

struct HitBox {
	EntityID ID;
	float x, y;
	float width; float height;
};


