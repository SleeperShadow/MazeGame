#pragma once

enum struct SiteType : unsigned char
{
  Wall,
  Door,
  Room,
  Maze,
};

class MapSite
{
public:
  virtual void enter() = 0;

  virtual SiteType type() = 0;

  virtual ~MapSite(){};
};
