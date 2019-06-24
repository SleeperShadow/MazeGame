#include "Room.h"
#include "ECS.h"
#include "Game.h"

Room::Room(int number)
  : _roomNumber(number)
{
  _manager = std::make_unique<Manager>();
}

MapSite*
Room::getSide(Direction d)
{
  return sides[d].get();
}

void
Room::setSide(Direction d, std::unique_ptr<MapSite> site)
{
  sides[d] = std::move(site);
}

void
Room::enter()
{
  Game::instance().setManager(_manager.get());
}

Room::~Room() {}
