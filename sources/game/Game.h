#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <vector>

class Manager;
class Entity;
class AssetManager;

class Game
{
public:
  void init(const char* title,
            int x,
            int y,
            int width,
            int height,
            bool fullscreen,
            Manager* m) noexcept;
  void handleEvents() noexcept;
  void update() noexcept;
  void render() noexcept;
  void cleanup() noexcept;

  bool running() const noexcept;

public:
  inline SDL_Renderer* getRenderer() { return renderer; }

  static Game& instance();

  Manager& getManager();

  void setManager(Manager* m);

  SDL_Event event;

  bool isRunning = false;

  SDL_Rect camera;

  std::unique_ptr<AssetManager> assets;

  ~Game();

public:
  enum GroupLabels : std::size_t
  {
    Map,
    Bricks,
    Players,
    Enemies,
    Projectiles,
  };

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Manager* manager;
  Entity* player;

  int _width;
  int _height;

private:
  Game();
};
