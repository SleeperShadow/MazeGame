#include "ECS.h"

void Entity::addGroup(Group g) {
  groupBitset[g] = true;
  m.addToGroup(this, g);
}
