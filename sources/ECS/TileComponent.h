#pragma once
#include "AssetManager.h"
#include "ECS.h"
#include "SDL.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

class TileComponent : public Component {
public:
  SDL_Texture *tex;
  SDL_Rect src;
  SDL_Rect dst;
  Vector2D position;

public:
  TileComponent() = default;

  TileComponent(int srcX, int srcY, int x, int y, int tileSize, int tileScale,
                std::string const &texid) {
    tex = Game::instance().assets->getTexture(texid);

    position.x = static_cast<float>(x);
    position.y = static_cast<float>(y);

    src.x = srcX;
    src.y = srcY;
    src.w = src.w = tileSize;

    dst.x = x;
    dst.y = y;
    dst.w = dst.h = tileSize * tileScale;
  }

  void init() override { entity->addGroup(Game::GroupLabels::Map); }

  void update() override {
    dst.x = static_cast<int>(position.x - Game::instance().camera.x);
    dst.y = static_cast<int>(position.y - Game::instance().camera.y);
  }

  void draw() override { TextureManager::draw(tex, src, dst); }

  ~TileComponent() { SDL_DestroyTexture(tex); }
};
