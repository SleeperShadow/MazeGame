#include "Door.h"
#include "Room.h"
#include <algorithm>

Door::Door(Room* from, Room* to)
  : current(from)
  , other(to)
{}

void
Door::enter()
{
  std::swap(current, other);
  current->enter();
}

Room*
Door::getCurrentRoom()
{
  return current;
}

Room*
Door::otherSideOfDoor()
{
  return other;
}
