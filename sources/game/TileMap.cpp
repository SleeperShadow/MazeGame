#include "TileMap.h"
#include "AssetManager.h"
#include "ColliderComponent.h"
#include "ECS.h"
#include "Game.h"
#include "TileComponent.h"
#include <fstream>
#include <iostream>

void
TileMap::load(std::string const& path, int maxX, int maxY)
{
  char tile;
  std::fstream map(path);
  auto dstSize = _tileSize * _mapScale;

  Game::instance()
    .getManager()
    .getGroup(Game::GroupLabels::Map)
    .reserve(static_cast<size_t>(maxX * maxY));

  if (map.is_open()) {
    for (int y = 0; y < maxY; ++y) {
      for (int x = 0; x < maxX; ++x) {
        map.get(tile);
        auto srcY = std::atoi(&tile) * _tileSize;
        map.get(tile);
        auto srcX = std::atoi(&tile) * _tileSize;
        addTile(srcX, srcY, x * dstSize, y * dstSize);
        map.ignore();
      }
    }

    map.ignore();

    auto& manager = Game::instance().getManager();

    for (int y = 0; y < maxY; ++y) {
      for (int x = 0; x < maxX; ++x) {
        map.get(tile);
        if (tile == '1') {
          auto& collider = manager.addEntity();
          collider.addComponent<ColliderComponent>(
            "terrain", x * dstSize, y * dstSize, dstSize, 2);
          collider.addGroup(Game::GroupLabels::Walls);
        }
        map.ignore();
      }
    }
    map.close();
  }
}

TileMap::TileMap(std::string const& tid, int tileSize, int mapScale)
  : texid(tid)
  , _mapScale(mapScale)
  , _tileSize(tileSize)
{}

void
TileMap::addTile(int srcX, int srcY, int x, int y)
{
  auto& tile(Game::instance().getManager().addEntity());
  tile.addComponent<TileComponent>(
    srcX, srcY, x, y, _tileSize, _tileSize, _mapScale, texid);
}
