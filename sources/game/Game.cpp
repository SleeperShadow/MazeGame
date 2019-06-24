#include "Game.h"
#include "AssetManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "Components.h"
#include "ECS.h"
#include "TextureManager.h"
#include <iostream>

Game::Game()
  : isRunning(false)
  , window(nullptr)
  , renderer(nullptr)
{
  setManager(manager);
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
           bool fullscreen) noexcept
{
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

        assets->addTexture("player", "assets/player->png");
        assets->addTexture("terrain", "assets/terrain_ss.png");
        assets->addTexture("collider", "assets/ColTex.png");
        assets->addTexture("arrow", "assets/Arrow.png");

        isRunning = true;
        player->addComponent<TransformComponent>(
          Vector2D{ _width / 2.f, _height / 2.f },
          Vector2D{ 0.f, 0.f },
          22,
          32,
          1);
        player->addComponent<SpriteComponent>(
          "player",
          std::map<AnimationId, Animation>{
            std::make_pair<AnimationId, Animation>(AnimationId::Idle,
                                                   Animation{ 4, 100 }),
            std::make_pair<AnimationId, Animation>(AnimationId::Move,
                                                   Animation{ 13, 100 }) });

        player->addComponent<KeyboardController>();
        player->addComponent<ColliderComponent>("player");
        player->addGroup(GroupLabels::Players);

        assets->createProjectile(Vector2D{ _width / 2.f, _height / 2.f },
                                 Vector2D{ -1, -1 },
                                 10,
                                 3,
                                 "arrow");
        assets->createProjectile(
          Vector2D{ 0 / 2.f, 0 / 2.f }, Vector2D{ 1, 1 }, 10, 3, "arrow");

        camera = SDL_Rect{ 0, 0, _width, _height };
      }
    }
  }
}

void
Game::handleEvents() noexcept
{
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
  auto& colliders(manager->getGroup(Game::GroupLabels::Bricks));
  auto& projectiles(manager->getGroup(Game::GroupLabels::Projectiles));

  auto& playerCollider = player->getComponent<ColliderComponent>();
  Vector2D playerPosition = player->getComponent<TransformComponent>().pos;

  manager->refresh();
  manager->update();

  for (auto& collider : colliders) {
    if (Collision::AABB(playerCollider,
                        collider->getComponent<ColliderComponent>())) {
      player->getComponent<TransformComponent>().pos = playerPosition;
    }
  }

  for (auto& p : projectiles) {
    if (Collision::AABB(playerCollider, p->getComponent<ColliderComponent>())) {
      p->destroy();
    }
  }

  camera.x = static_cast<int>(player->getComponent<TransformComponent>().pos.x -
                              _width / 2);
  camera.y = static_cast<int>(player->getComponent<TransformComponent>().pos.y -
                              _height / 2);

  if (camera.x < 0)
    camera.x = 0;
  if (camera.y < 0)
    camera.y = 0;
  if (camera.x > camera.w)
    camera.x = camera.w;
  if (camera.y > camera.h)
    camera.y = camera.h;
}

void
Game::render() noexcept
{
  SDL_RenderClear(renderer);

  auto& tiles(manager->getGroup(Game::GroupLabels::Map));
  auto& players(manager->getGroup(Game::GroupLabels::Players));
  auto& enemies(manager->getGroup(Game::GroupLabels::Enemies));
  auto& projectiles(manager->getGroup(Game::GroupLabels::Enemies));

  for (auto& tile : tiles) {
    tile->draw();
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
  assets->changeManager(manager);
}
