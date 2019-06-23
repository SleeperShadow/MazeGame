#pragma once
#include <string>

class TileMap {
public:
  TileMap(std::string const &path, int mapScale, int tileSize);

  void addTile(int srcX, int srcY, int x, int y);
  void load(std::string const &path, int maxX, int maxY);

private:
  std::string texid;
  int _mapScale;
  int _tileSize;
};
