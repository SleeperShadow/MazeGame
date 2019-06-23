#include "Game.h"
#include "AssetManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "Components.h"
#include "ECS.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "TileMap.h"
#include <iostream>

std::unique_ptr<TileMap> map;

std::unique_ptr<Manager> manager{new Manager()};

auto &player = manager -> addEntity();

Game::Game()
    : isRunning(false), window(nullptr), renderer(nullptr),
      assets(new AssetManager(manager.get())) {}

Game::~Game() { cleanup(); }

void Game::init(const char *title, int x, int y, int width, int height,
                bool fullscreen) noexcept {
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
        assets->addTexture("terrain", "assets/terrain_ss.png");
        assets->addTexture("collider", "assets/ColTex.png");

        isRunning = true;
        player.addComponent<TransformComponent>(_width / 2.f, 220.f, 22, 32, 2);
        player.addComponent<SpriteComponent>("player", true);
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        player.addGroup(GroupLabels::Players);

        map.reset(new TileMap("terrain", 32, 2));
        map->load("assets/map.map", 25, 20);

        camera = SDL_Rect{0, 0, _width, _height};
      }
    }
  }
}

auto &tiles(manager->getGroup(Game::GroupLabels::Map));
auto &players(manager->getGroup(Game::GroupLabels::Players));
auto &colliders(manager->getGroup(Game::GroupLabels::Colliders));
auto &enemies(manager->getGroup(Game::GroupLabels::Enemies));

void Game::handleEvents() noexcept {
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() noexcept {
  SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
  Vector2D playerPosition = player.getComponent<TransformComponent>().pos;

  manager->refresh();
  manager->update();

  for (auto &collider : colliders) {
    SDL_Rect temp = collider->getComponent<ColliderComponent>().collider;

    if (Collision::AABB(temp, playerCollider)) {
      player.getComponent<TransformComponent>().pos = playerPosition;
    }
  }

  camera.x = static_cast<int>(player.getComponent<TransformComponent>().pos.x -
                              _width / 2);
  camera.y = static_cast<int>(player.getComponent<TransformComponent>().pos.y -
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

void Game::render() noexcept {
  SDL_RenderClear(renderer);

  for (auto &tile : tiles) {
    tile->draw();
  }
  for (auto &collider : colliders) {
    collider->draw();
  }

  for (auto &p : players) {
    p->draw();
  }

  for (auto &enemy : enemies) {
    enemy->draw();
  }

  SDL_RenderPresent(renderer);
}

void Game::cleanup() noexcept {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Cleanup done" << std::endl;
}

bool Game::running() const noexcept { return isRunning; }

Game &Game::instance() {
  static std::unique_ptr<Game> game{new Game()};

  return *game;
}

Manager &Game::getManager() { return *manager; }
