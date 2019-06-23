#pragma once
#include "Animation.h"
#include "AssetManager.h"
#include "Game.h"
#include "TransformComponent.h"
#include <map>

class SpriteComponent : public Component {
private:
  TransformComponent *transform;
  SDL_Texture *tex;
  SDL_Rect src;
  SDL_Rect dst;

  bool animated = false;
  int frames = 0;
  int speed = 100;

public:
  int animationId;

  SDL_RendererFlip spriteFlipped = SDL_FLIP_NONE;

  std::map<std::string, Animation> animations;

public:
  SpriteComponent(std::string const &texid) { setTex(texid); }
  SpriteComponent(std::string const &texid, bool animate) : animated(animate) {

    animations.emplace("Idle", Animation{0, 4, 100});
    animations.emplace("Walk", Animation{1, 13, 100});

    play("Idle");

    setTex(texid);
  }

  void setTex(std::string const &texid) {
    tex = Game::instance().assets->getTexture(texid);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    src.x = 0;
    src.y = 0;
    src.w = static_cast<int>(transform->width);
    src.h = static_cast<int>(transform->height);
  }

  void update() override {
    if (animated) {
      src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }

    src.y = animationId * transform->height;

    dst.x = static_cast<int>(transform->pos.x - Game::instance().camera.x);
    dst.y = static_cast<int>(transform->pos.y - Game::instance().camera.y);
    dst.w = static_cast<int>(transform->width * transform->scale);
    dst.h = static_cast<int>(transform->height * transform->scale);
  }

  void draw() override { TextureManager::draw(tex, src, dst, spriteFlipped); }

  void play(std::string const &animation) {
    auto &anim = animations[animation];
    frames = anim.frames;
    speed = anim.speed;
    animationId = anim.index;
  }
};
