#pragma once
#include "EntityID.h"
#include <iostream>
#include <tuple>
#include <optional>

struct Position {
	EntityID& ID;
	float x = 0.0f , y = 0.0f;

	Position(EntityID& startID, float startX, float startY) 
		: ID(startID), x(startX), y(startY) {}
	Position(EntityID& startID)
		: ID(startID), x(0.0f), y(0.0f) {
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

	auto GetElems() const {
		return make_tuple(x, y);
	}

	void PrintElem() {
		cout << "[x, y] = [" 
			<< x
			<< ", " 
			<< y 
			<< "] \n";
	}

	void Reset() {
		x = 0.0; y = 0.0;
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

	auto GetElems() const {
		return make_tuple(width, height);
	}


	const void PrintElem() {
		cout << "[w, h] = ["
			<< width
			<< ", "
			<< height 
			<< "] \n";
	}

	void Reset() {
		width = 0.0; height = 0.0;
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

	auto GetElems() const {
		return make_tuple(velocity);
	}

	const void PrintElem() {
		cout << " Velocity = ["
			<< velocity
			<< "] \n";
	}

	void Reset() {
		velocity = 0.0; 
	}


};

struct HitBox {
	EntityID ID;
	float x, y;
	float width; float height;
};


