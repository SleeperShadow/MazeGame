#include "Maze.h"

void
Maze::enter()
{
  if (_rooms.size() > 0)
    _rooms[0]->enter();
}
