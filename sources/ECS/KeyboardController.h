#pragma once
#include "Animation.h"
#include "ECS.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

class KeyboardController : public Component
{
public:
  TransformComponent* transform;
  SpriteComponent* sprite;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
  }

  void update() override
  {
    if (Game::instance().event.type == SDL_KEYDOWN) {
      switch (Game::instance().event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = -1;
          sprite->play(AnimationId::Move);
          break;
        case SDLK_s:
          transform->velocity.y = 1;
          sprite->play(AnimationId::Move);
          break;
        case SDLK_a:
          transform->velocity.x = -1;
          sprite->play(AnimationId::Move);
          break;
        case SDLK_d:
          transform->velocity.x = 1;
          sprite->play(AnimationId::Move);
          break;
        default:
          break;
      }
    }

    if (Game::instance().event.type == SDL_KEYUP) {
      switch (Game::instance().event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = 0;
          sprite->play(AnimationId::Idle);
          break;
        case SDLK_s:
          transform->velocity.y = 0;
          sprite->play(AnimationId::Idle);
          break;
        case SDLK_a:
          transform->velocity.x = 0;
          sprite->play(AnimationId::Idle);
          break;
        case SDLK_d:
          transform->velocity.x = 0;
          sprite->play(AnimationId::Idle);
          break;
        case SDLK_ESCAPE:
          Game::instance().isRunning = false;
          break;
        default:
          break;
      }
    }
  }
};
