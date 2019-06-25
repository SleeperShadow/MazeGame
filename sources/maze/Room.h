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
  Room(std::size_t number);

  MapSite* getSide(Direction);
  void setSide(Direction, std::unique_ptr<MapSite> site);

  virtual void enter() override;
  virtual SiteType type() override { return SiteType::Room; };

  Manager* getManager() const;

  ~Room();

private:
  std::array<std::unique_ptr<MapSite>, 4> sides;
  std::size_t _roomNumber;
  std::unique_ptr<Manager> _manager;
};
