#include "MazeBuilder.h"
#include "Components.h"
#include "Door.h"
#include "ECS.h"
#include <memory>
#include <random>

const int wallSize = 64;
const auto sc = 2;
const auto scaledSize = wallSize * sc;

MazeBuilder::MazeBuilder(int lvl)
  : level(lvl)
{}

void
MazeBuilder::buildMaze()
{
  maze = std::make_unique<Maze>();
  lastCreatedRoom = -1;

  for (int i = 0; i < level; ++i) {
    buildRoom();
  }

  other = std::make_unique<MazeBuilder>(level + 1);
  static_cast<Door*>(maze->getRoom(lastCreatedRoom)->getSide(Direction::East))
    ->otherSideOfDoor() = other.get();
}

std::unique_ptr<MapSite>
MazeBuilder::buildHorizontalWall(Vector2D start, Vector2D end)
{
  auto wall = std::make_unique<Wall>();

  for (auto x = start.x; x < end.x; x += scaledSize) {
    buildWallPiece(
      0, 0, (int)x, (int)end.y, wallSize, wallSize, sc, wall.get());
  }

  return wall;
}

Entity&
MazeBuilder::buildWallPiece(int srcX,
                            int srcY,
                            int dstX,
                            int dstY,
                            int wallSizeX,
                            int wallSizeY,
                            int scale,
                            MapSite* owner)
{
  auto& wallpiece = currentRoomManager->addEntity();
  wallpiece.addComponent<TileComponent>(
    srcX, srcY, dstX, dstY, wallSizeX, wallSizeY, scale, "wall");
  wallpiece.addComponent<WallComponent>(owner);

  return wallpiece;
}

Entity&
MazeBuilder::buildDoorPiece(int srcX,
                            int srcY,
                            int dstX,
                            int dstY,
                            int wallSizeX,
                            int wallSizeY,
                            int scale,
                            Door* owner)
{
  auto& doorpiece = currentRoomManager->addEntity();
  doorpiece.addComponent<TileComponent>(
    srcX, srcY, dstX, dstY, wallSizeX, wallSizeY, scale, "door");
  doorpiece.addComponent<DoorComponent>(owner);

  return doorpiece;
}

Room&
MazeBuilder::buildRoom()
{
  auto& room = maze->createRoom();
  currentRoomManager = room.getManager();

  auto northWall = buildHorizontalWall(
    Vector2D{ 0, 0 }, Vector2D{ Game::instance()._width * level, 0 });

  auto southWall =
    buildHorizontalWall(Vector2D{ 0, Game::instance()._height * level },
                        Vector2D{ Game::instance()._width * level,
                                  Game::instance()._height * level });
  room.setSide(Direction::South, std::move(southWall));
  room.setSide(Direction::North, std::move(northWall));

  auto prevRoom = maze->getRoom(lastCreatedRoom);
  if (prevRoom)
    static_cast<Door*>(prevRoom->getSide(Direction::East))->otherSideOfDoor() =
      &room;

  auto westDoor = buildDoor(maze->getRoom(lastCreatedRoom - 1),
                            &room,
                            Vector2D{ 0, 0 },
                            Vector2D{ 0, Game::instance()._height * level });
  auto eastDoor = buildDoor(&room,
                            nullptr,
                            Vector2D{ Game::instance()._width * level, 0 },
                            Vector2D{ Game::instance()._width * level,
                                      Game::instance()._height * level });

  room.setSide(Direction::East, std::move(eastDoor));
  room.setSide(Direction::West, std::move(westDoor));

  addTiles();
  spawnEnemies();

  lastCreatedRoom++;
  return room;
}

std::unique_ptr<Door>
MazeBuilder::buildDoor(MapSite* from, MapSite* to, Vector2D start, Vector2D end)
{
  auto wall = std::make_unique<Wall>();
  auto doorPos = end.y / 2 - wallSize;

  for (auto y = start.y; y < doorPos; y += scaledSize) {
    buildWallPiece(
      0, 0, (int)start.x, (int)y, wallSize, wallSize, sc, wall.get());
  }

  auto door = std::make_unique<Door>(from, to);

  buildDoorPiece(
    0, 0, (int)start.x, (int)doorPos, wallSize, wallSize, sc, door.get());

  for (auto y = doorPos + scaledSize; y < end.y; y += scaledSize) {
    buildWallPiece(
      0, 0, (int)start.x, (int)y, wallSize, wallSize, sc, wall.get());
  }
  return door;
}

Maze&
MazeBuilder::getMaze()
{
  return *maze;
}

void
MazeBuilder::spawnEnemies()
{
  std::random_device dev;
  std::mt19937 rng(dev());
  auto m = std::min(Game::instance()._width, Game::instance()._height);
  std::uniform_int_distribution<std::mt19937::result_type> dist(
    scaledSize, m * level - scaledSize);

  auto hardness = level * level;
  for (int lvl = 0; lvl < hardness * (lastCreatedRoom + 2); ++lvl) {
    spawnMeleeEnemy(Vector2D{ dist(rng), dist(rng) });
  }
}

void
MazeBuilder::spawnMeleeEnemy(Vector2D pos)
{
  auto& enemy = currentRoomManager->addEntity();
  enemy.addComponent<TransformComponent>(pos, Vector2D{ 1, 1 }, 24, 32, 2);
  enemy.addComponent<SpriteComponent>(
    "axe_skeleton",
    std::map<AnimationId, Animation>{
      std::make_pair<AnimationId, Animation>(AnimationId::Idle,
                                             Animation{ 11, 100, 24, 32 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Move,
                                             Animation{ 13, 100, 20, 32 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Attack,
                                             Animation{ 17, 100, 34, 34 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Death,
                                             Animation{ 15, 100, 32, 32 }) });

  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addGroup(Game::GroupLabels::Enemies);
}

void
MazeBuilder::spawnRangedEnemy(Vector2D pos)
{
  (void)pos;
}

void
MazeBuilder::addTiles()
{
  auto toX = Game::instance()._width * level;
  auto toY = Game::instance()._height * level;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

  for (int x = 0; x < toX; x += scaledSize) {
    for (int y = 0; y < toY; y += scaledSize) {
      auto& tile1(currentRoomManager->addEntity());
      auto tex = dist(rng) == 1 ? 512 : 0;
      auto& tc = tile1.addComponent<TileComponent>(
        (int)tex, 0, x, y, wallSize, wallSize, sc, "grass");
      SDL_SetTextureAlphaMod(tc.tex, 169);
      auto& tile2(currentRoomManager->addEntity());
      auto tex2 = tex == 0 ? 768 : 256;
      auto& tc2 = tile2.addComponent<TileComponent>(
        (int)tex2, 0, x, y, wallSize, wallSize, sc, "grass");
      SDL_SetTextureAlphaMod(tc2.tex, 100);
    }
  }
}

void
MazeBuilder::enter()
{
  if (!maze)
    buildMaze();

  maze->enter();
}

SiteType
MazeBuilder::type()
{
  return SiteType::Maze;
}
