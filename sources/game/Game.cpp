#include "Game.h"
#include "AssetManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "Components.h"
#include "ECS.h"
#include "TextureManager.h"
#include <iostream>

void
createPlayer(Entity*& player);

Game::Game()
  : isRunning(false)
  , window(nullptr)
  , renderer(nullptr)
{
  assets = std::make_unique<AssetManager>();
}

Game::~Game()
{
  cleanup();
}

void
Game::init(const char* title,
           int x,
           int y,
           int width,
           int height,
           bool fullscreen,
           Manager* m) noexcept
{
  setManager(m);

  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
  isRunning = false;
  _width = width;
  _height = height;

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "SDL initialized" << std::endl;
    window = SDL_CreateWindow(title, x, y, _width, _height, flags);
    if (window) {
      std::cout << "Window created" << std::endl;

      renderer = SDL_CreateRenderer(window, -1, 0);

      if (renderer) {
        std::cout << "Renderer created" << std::endl;

        assets->addTexture("player", "assets/player.png");
        assets->addTexture("grass", "assets/grass.png");
        assets->addTexture("wall", "assets/wall.png");
        assets->addTexture("axe_skeleton", "assets/axe_skeleton.png");
        assets->addTexture("abyssRanger", "assets/AbyssRanger.png");
        assets->addTexture("door", "assets/door.png");
        assets->addTexture("arrow", "assets/arrow.png");

        createPlayer(player);

        isRunning = true;

        camera = SDL_Rect{ 0, 0, _width, _height };
      }
    }
  }
}

void
Game::handleEvents() noexcept
{
  event = SDL_Event();
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void
Game::update() noexcept
{
  auto& colliders(manager->getGroup(Game::GroupLabels::Walls));
  auto& doors(manager->getGroup(Game::GroupLabels::Doors));
  auto& projectiles(manager->getGroup(Game::GroupLabels::Projectiles));
  auto& enemies(manager->getGroup(Game::GroupLabels::Enemies));
  auto& players(manager->getGroup(Game::GroupLabels::Players));

  ColliderComponent* playerCollider = nullptr;
  Vector2D playerPosition{ 0, 0 };

  if (players.size()) {
    playerCollider = &player->getComponent<ColliderComponent>();
    playerPosition = player->getComponent<TransformComponent>().pos;
  }

  manager->update();
  manager->refresh();

  if (players.size()) {
    for (auto& wall : colliders) {
      if (Collision::AABB(*playerCollider,
                          wall->getComponent<ColliderComponent>())) {
        player->getComponent<TransformComponent>().pos = playerPosition;
      }
      for (auto& e : enemies) {
        if (Collision::AABB(e->getComponent<ColliderComponent>().collider,
                            wall->getComponent<ColliderComponent>().collider)) {
          e->getComponent<TransformComponent>().velocity.x *= -1;
          e->getComponent<TransformComponent>().velocity.y *= -1;
        }
      }
    }
    for (auto& door : doors) {
      if (enemies.empty())
        door->getComponent<DoorComponent>().owner->open();

      if (Collision::AABB(*playerCollider,
                          door->getComponent<ColliderComponent>())) {
        if (door->getComponent<DoorComponent>().owner->opened())
          door->getComponent<DoorComponent>().collide();
        else
          player->getComponent<TransformComponent>().pos = playerPosition;
      }
    }

    for (auto& p : projectiles) {
      if (Collision::AABB(*playerCollider,
                          p->getComponent<ColliderComponent>())) {
        //p->destroy();
      }
      for (auto& e : enemies) {
        if (Collision::AABB(e->getComponent<ColliderComponent>().collider,
                            p->getComponent<ColliderComponent>().collider)) {
          e->destroy();
        }
      }
    }
    for (auto& e : enemies) {
      if (Collision::AABB(e->getComponent<ColliderComponent>().collider,
                          playerCollider->collider)) {
        e->getComponent<SpriteComponent>().play(AnimationId::Attack);
        e->getComponent<TransformComponent>().velocity = Vector2D{ 0, 0 };
        player->getComponent<HealthComponent>().health -= 1;
      } else if (e->getComponent<SpriteComponent>().animationId ==
                 AnimationId::Attack) {
        e->getComponent<SpriteComponent>().play(AnimationId::Move);
        e->getComponent<TransformComponent>().velocity = Vector2D{ 1, 1 };
      }
    }

    camera.x = static_cast<int>(
      player->getComponent<TransformComponent>().pos.x - _width / 2);
    camera.y = static_cast<int>(
      player->getComponent<TransformComponent>().pos.y - _height / 2);
  }
  if (camera.x < 0)
    camera.x = 0;
  if (camera.y < 0)
    camera.y = 0;
}

void
Game::render() noexcept
{
  SDL_RenderClear(renderer);

  auto& tiles(manager->getGroup(Game::GroupLabels::Map));
  auto& walls(manager->getGroup(Game::GroupLabels::Walls));
  auto& doors(manager->getGroup(Game::GroupLabels::Doors));
  auto& players(manager->getGroup(Game::GroupLabels::Players));
  auto& enemies(manager->getGroup(Game::GroupLabels::Enemies));
  auto& projectiles(manager->getGroup(Game::GroupLabels::Projectiles));

  for (auto& tile : tiles) {
    tile->draw();
  }
  for (auto& wall : walls) {
    wall->draw();
  }
  for (auto& door : doors) {
    door->draw();
  }

  for (auto& p : players) {
    p->draw();
  }

  for (auto& enemy : enemies) {
    enemy->draw();
  }

  for (auto& proj : projectiles) {
    proj->draw();
  }

  SDL_RenderPresent(renderer);
}

void
Game::cleanup() noexcept
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Cleanup done" << std::endl;
}

bool
Game::running() const noexcept
{
  return isRunning;
}

Game&
Game::instance()
{
  static std::unique_ptr<Game> game{ new Game() };

  return *game;
}

Manager&
Game::getManager()
{
  return *manager;
}

void
Game::setManager(Manager* m)
{
  manager = m;
  if (player)
    createPlayer(player);
}

void
createPlayer(Entity*& player)
{
  auto& newManager = Game::instance().getManager();

  if (player)
    player->destroy();

  player = &newManager.addEntity();
  player->addComponent<TransformComponent>(
    Vector2D{ 128.f, Game::instance()._height / 2.f },
    Vector2D{ 0.f, 0.f },
    32,
    32,
    2);
  player->addComponent<SpriteComponent>(
    "player",
    std::map<AnimationId, Animation>{
      std::make_pair<AnimationId, Animation>(AnimationId::Idle,
                                             Animation{ 10, 100, 32, 32 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Move,
                                             Animation{ 10, 100, 32, 32 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Attack,
                                             Animation{ 10, 100, 32, 32 }),
      std::make_pair<AnimationId, Animation>(AnimationId::Death,
                                             Animation{ 10, 100, 32, 32 }) });

  player->addComponent<KeyboardController>();
  player->addComponent<ColliderComponent>("player");
  player->addComponent<HealthComponent>(100);
  player->addComponent<MouseController>();
  player->addGroup(Game::GroupLabels::Players);
}