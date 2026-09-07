#include "Entity.h"
#include "Registry.h"

void Entity::Position(float x, float y) {
    registry->AddPosition(ID, x, y);
}
