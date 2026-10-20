#pragma once

#include "Components.h"

struct MovementSystem {
	uint64_t ID;
	MovementSystem(uint64_t startID) : ID(startID) {}

	void Print_Add() {
		cout << "ID" << ID << ": Success! MovementSystem Add \n";
	}
};