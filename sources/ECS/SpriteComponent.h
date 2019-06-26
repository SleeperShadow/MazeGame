#pragma once
#include "Animation.h"
#include "AssetManager.h"
#include "Game.h"
#include "TransformComponent.h"
#include <map>

class SpriteComponent : public Component
{
public:
  TransformComponent* transform;
  SDL_Texture* tex;
  SDL_Rect src;
  SDL_Rect dst;

  bool animated = false;
  int frames = 1;
  int speed = 50;

public:
  AnimationId animationId = AnimationId::Idle;

  SDL_RendererFlip spriteFlipped = SDL_FLIP_NONE;

  std::map<AnimationId, Animation> animations;

  double angle = 0;

public:
  SpriteComponent(std::string const& texid, bool animate = false)
    : animated(animate)
  {
    setTex(texid);
  }

  SpriteComponent(std::string const& texid, int srcX, int srcY)
    : animated(false)
  {
    setTex(texid);
    src.x = srcX;
    src.y = srcY;
  }

  SpriteComponent(std::string const& texid,
                  std::map<AnimationId, Animation>&& anims)
    : animated(true)
    , animations(std::forward<std::map<AnimationId, Animation>>(anims))
  {
    src.x = src.y = 0;
    setTex(texid);
  }

  void setTex(std::string const& texid)
  {
    tex = Game::instance().assets->getTexture(texid);
  }

  void setAnimations(std::map<AnimationId, Animation>&& anims)
  {
    animations = std::forward<std::map<AnimationId, Animation>>(anims);
  }

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();

    src.w = static_cast<int>(transform->width);
    src.h = static_cast<int>(transform->height);
  }

  void update() override
  {
    if (animated) {
      src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }
    src.y = animationId * transform->height;

    if (transform->velocity.x >= 0) {
      spriteFlipped = SDL_FLIP_NONE;
    } else if (transform->velocity.x < 0)
      spriteFlipped = SDL_FLIP_HORIZONTAL;

    if (animationId != AnimationId::Attack && animated) {
      if (transform->velocity.x != 0 ||
          transform->velocity.y != 0 &&
            animations.find(AnimationId::Move) != animations.end())
        play(AnimationId::Move);
      else
        play(AnimationId::Idle);
    }

    dst.x = static_cast<int>(transform->pos.x - Game::instance().camera.x);
    dst.y = static_cast<int>(transform->pos.y - Game::instance().camera.y);
    dst.w = static_cast<int>(transform->width * transform->scale);
    dst.h = static_cast<int>(transform->height * transform->scale);
  }

  void draw() override
  {
    TextureManager::draw(tex, src, dst, spriteFlipped, angle);
  }

  void play(AnimationId id)
  {
    auto& anim = animations[id];
    frames = anim.frames;
    speed = anim.speed;
    if (transform != nullptr) {
      transform->width = anim.width;
      transform->height = anim.height;
    }
    animationId = id;
  }
};
