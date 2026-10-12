#pragma once
#include "Components.h"
#include <type_traits>

class Storage {
	vector<Position> pos;
	vector<Dimension> dim;
	vector<HitBox> HB;

	template<typename T>
	vector<T>& GetComponents() {
		if constexpr(is_same_v<T, Position>) {
			return pos;
		} 
		else if constexpr(is_same_v<T, Dimension>) {
			return dim;
		}
		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported component type");
		}
	}

	template<typename T>
	string PrintComponents() {
		if constexpr (is_same_v<T, Position>) return "Position";

		else if constexpr (is_same_v<T, Dimension>) return "Dimension";

		else {
			static_assert(std::is_same_v<T, void>,
				"Unsupported component type");
		}
	
	}
 
	template<typename T>
	bool FindComponents(EntityID& startID, const vector<T>& components) {
		for (int i = 0; i < components.size(); i++) {
			if (&components[i].ID == &startID) {
				return true;
			}
		}
		return false;
	}
	template<typename T>
	void FindComponents(EntityID& startID, vector<T>& components, T*& result) {
		for (auto& component : components) {
			if (&component.ID == &startID) {
				result = &component;
				return;
			}
		}
		result = nullptr;
	}

	template<typename T>
	void AddComponents(EntityID& ID, vector<T>& components, float Element_1, float Element_2) {
		T* component = nullptr;
		FindComponents(ID, components, component);

		if (component == nullptr) {
			T new_component(ID, Element_1, Element_2);
			components.push_back(new_component);
		}
		else {
			component -> Set(Element_1, Element_2);

			cout << "ID:" << ID.PrintID() << " Success! Template " 
				<< PrintComponents<T>() << " rebut. "
				<< "[x, y] = [" << component -> Get_elem_1() 
				<< ", " << component -> Get_elem_2() << "]\n";
		}
	}

public:

	template<typename T>
	void AddComponents(EntityID& ID, float Element_1, float Element_2) {
		auto& components = GetComponents<T>();
		AddComponents(ID, components, Element_1, Element_2);
	}

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
	


	bool FindDimension(EntityID& startID) {
		for (int i = 0; i < dim.size(); i++) {
			if (&dim[i].ID == &startID) {
				return true;
				break;
			}
		}
		return false;
	}
	void FindDimension(EntityID& startID, auto*& startDim) {
		for (auto& component : dim) {
			if (&component.ID == &startID) {
				startDim = &component;
				break; 
			}
		}
	}

	void addDim(EntityID& ID, float startWidth, float startWeight) {
		Dimension* dimetion = nullptr;
		FindDimension(ID, dimetion);
		if (dimetion == nullptr) {
			Dimension dimension(ID, startWidth, startWeight);
			dim.push_back(dimension);
		}
		else {
			dimetion->width = startWidth;
			dimetion->height = startWeight;
			cout << "ID:" << ID.PrintID() << " Success! Dimension rebut. "
				<< "[x, y] = [" << dimetion->width << ", " << dimetion->height << "]\n";
		}
	}



};
