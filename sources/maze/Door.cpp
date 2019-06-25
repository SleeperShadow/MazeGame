#include "Door.h"
#include <algorithm>

Door::Door(MapSite* from, MapSite* to)
  : current(from)
  , other(to)
{}

void
Door::enter()
{
  if (other && isOpen)
    other->enter();
}

void
Door::open()
{
  isOpen = true;
}

MapSite*&
Door::currentSideOfDoor()
{
  return current;
}

MapSite*&
Door::otherSideOfDoor()
{
  return other;
}
