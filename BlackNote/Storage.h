#pragma once
#include "Components.h"


class Storage {
	vector<Position> pos;
	vector<Dimension> dim;
	vector<HitBox> HB;

public:

	bool FindPosition(EntityID& startID) {
		for (int i = 0; i < pos.size(); i++) {
			if ( &pos[i].ID == &startID) {
				return true;
				break;
			}
		}
		return false;
	}
	void FindPosition(EntityID& startID, Position*& startPos) {
		for (auto& position : pos) {
			if (&position.ID == &startID) {
				startPos = &position;
				break;
			}
		}
	}

	void addPos(EntityID& ID, float startX, float startY) {
		Position* position = nullptr;
		FindPosition(ID, position);

		if (position == nullptr) {
			Position position(ID, startX, startY);
			pos.push_back(position);
		}
		else {
			position->x = startX;
			position->y = startY;
			cout << "ID:" << ID.PrintID() << " Success! Position rebut. "
				<< "[x, y] = [" << position->x << ", " << position->y << "]\n";
		}
	}
	

	
	void addDim(EntityID& ID, float width, float height) {
		Dimension dimension(ID, width, height);
		dim.push_back(dimension);
	}
	bool FindDimension(EntityID& startID) {
		for (int i = 0; i < dim.size(); i++) {
			if (&dim[i].ID == &startID) {
				return true;
				break;
			}
		}
		return false;
	}


};
