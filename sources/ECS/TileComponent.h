#pragma once
#include "AssetManager.h"
#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"

class TileComponent : public Component
{
public:
  SDL_Texture* tex;
  SDL_Rect src;
  SDL_Rect dst;
  Vector2D position;

public:
  TileComponent() = default;

  TileComponent(int srcX,
                int srcY,
                int dstX,
                int dstY,
                int tileSizeX,
                int tileSizeY,
                int scale,
                std::string const& texid)
  {
    tex = Game::instance().assets->getTexture(texid);
    position.x = static_cast<float>(dstX);
    position.y = static_cast<float>(dstY);

    src.x = srcX;
    src.y = srcY;
    src.w = tileSizeX;
    src.h = tileSizeY;

    dst.x = dstX;
    dst.y = dstY;
    dst.w = src.w * scale;
    dst.h = src.h * scale;
  }

  void init() override { entity->addGroup(Game::GroupLabels::Map); }

  void update() override
  {
    dst.x = static_cast<int>(position.x - Game::instance().camera.x);
    dst.y = static_cast<int>(position.y - Game::instance().camera.y);
  }

  void draw() override { TextureManager::draw(tex, src, dst); }
};
