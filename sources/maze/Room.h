#pragma once
#include "MapSite.h"
#include <array>

enum Direction : unsigned char
{
  North = 0,
  South,
  East,
  West,
};

class Manager;

class Room : public MapSite
{
public:
  Room(int number);

  MapSite* getSide(Direction);
  void setSide(Direction, std::unique_ptr<MapSite> site);

  virtual void enter() override;

  ~Room();

private:
  std::array<std::unique_ptr<MapSite>, 4> sides;
  int _roomNumber;
  std::unique_ptr<Manager> _manager;
};
