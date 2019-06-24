#pragma once
#include "Door.h"
#include "MapSite.h"
#include "Room.h"
#include <memory>

class Maze : public MapSite
{
public:
  virtual std::unique_ptr<Maze> create() const
  {
    return std::make_unique<Maze>();
  }

  virtual std::unique_ptr<Room> createRoom(int roomNumber) const
  {
    return std::make_unique<Room>(roomNumber);
  }

  virtual std::unique_ptr<Door> createDoor(Room* from, Room* to) const
  {
    return std::make_unique<Door>(from, to);
  }

  virtual void enter() override;
};
