#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <vector>

class ColliderComponent;
class Manager;
class AssetManager;

class Game {
public:
  void init(const char *title, int x, int y, int width, int height,
            bool fullscreen) noexcept;
  void handleEvents() noexcept;
  void update() noexcept;
  void render() noexcept;
  void cleanup() noexcept;

  bool running() const noexcept;

public:
  inline SDL_Renderer *getRenderer() { return renderer; }

  static Game &instance();

  Manager &getManager();

  SDL_Event event;

  bool isRunning = false;

  SDL_Rect camera;

  std::unique_ptr<AssetManager> assets;

  ~Game();

public:
  enum GroupLabels : std::size_t {
    Map,
    Players,
    Enemies,
    Colliders,
  };

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  int _width;
  int _height;

private:
  Game();
};
