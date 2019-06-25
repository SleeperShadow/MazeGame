#pragma once
#include "Maze.h"
#include "Vector2d.h"
#include "Wall.h"

class Entity;
class Manager;

class MazeBuilder : public MapSite
{
public:
  MazeBuilder(int lvl);

  virtual void buildMaze();

  virtual std::unique_ptr<MapSite> buildHorizontalWall(Vector2D start,
                                                       Vector2D end);

  virtual Entity& buildWallPiece(int srcX,
                                 int srcY,
                                 int dstX,
                                 int dstY,
                                 int wallSizeX,
                                 int wallSizeY,
                                 int scale,
                                 MapSite* owner);

  virtual Entity& buildDoorPiece(int srcX,
                                 int srcY,
                                 int dstX,
                                 int dstY,
                                 int wallSizeX,
                                 int wallSizeY,
                                 int scale,
                                 Door* owner);

  virtual Room& buildRoom();
  virtual std::unique_ptr<Door> buildDoor(MapSite* from,
                                          MapSite* to,
                                          Vector2D start,
                                          Vector2D end);

  Maze& getMaze();

  virtual void spawnEnemies();

  virtual void spawnMeleeEnemy(Vector2D pos);

  virtual void spawnRangedEnemy(Vector2D pos);

  virtual void addTiles();

public:
  // Inherited via MapSite
  virtual void enter() override;
  virtual SiteType type() override;

protected:
  std::unique_ptr<Maze> maze;
  Manager* currentRoomManager = nullptr;
  std::unique_ptr<MapSite> other;

  int level;
  int lastCreatedRoom = -1;
};
