#pragma once
#include "MapSite.h"

class Room;

class Door : public MapSite
{
public:
  Door(Room* from, Room* to);

  virtual void enter() override;

  Room* getCurrentRoom();
  Room* otherSideOfDoor();

private:
  Room* current;
  Room* other;
};
