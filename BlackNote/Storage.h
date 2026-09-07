#pragma once
#include "Components.h"


class Storage {
	vector<Position> pos;
	vector<Dimension> dimension;
	vector<HitBox> HB;

public:
	void addPos(EntityID& ID, float x, float y) {
		Position position(ID, x, y);
		pos.push_back(position);
	}



};
