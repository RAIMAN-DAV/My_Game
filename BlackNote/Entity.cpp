#include "Entity.h"
#include "Registry.h"

void Entity::Position(float x, float y) {
    registry->AddComponent < ::Position > (ID.PrintID(), x, y);
}
void Entity::Dimension(float width, float height) {
    registry->AddComponent< ::Dimension > (ID.PrintID(), width, height);
}
