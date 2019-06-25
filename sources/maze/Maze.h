#pragma once
#include "Door.h"
#include "MapSite.h"
#include "Room.h"
#include <memory>
#include <vector>

class Maze : public MapSite
{
public:
  virtual std::unique_ptr<Maze> create() const
  {
    return std::make_unique<Maze>();
  }

  virtual Room& createRoom() const
  {
    _rooms.emplace_back(new Room(_rooms.size()));
    return *_rooms.back();
  }

  Room* getRoom(int roomNumber) const
  {
    return roomNumber >= _rooms.size() || roomNumber < 0
             ? nullptr
             : _rooms[roomNumber].get();
  }

  virtual void enter() override;
  virtual SiteType type() override { return SiteType::Maze; };

private:
  mutable std::vector<std::unique_ptr<Room>> _rooms;
};
