#pragma once
#include "Components.h"


class storage {
	vector<Position> pos;
	vector<Dimension> dimension;
	vector<HitBox> HB;

public:
	void addPos(EntityID ID) {
		pos.push_back(ID, x, y);
	}



};
