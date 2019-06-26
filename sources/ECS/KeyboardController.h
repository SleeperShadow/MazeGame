#pragma once
#include "Animation.h"
#include "ECS.h"
#include "Game.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"

class KeyboardController : public Component
{
public:
  TransformComponent* transform;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
  }

  void update() override
  {
    if (Game::instance().event.type == SDL_KEYDOWN) {
      switch (Game::instance().event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = -1;
          break;
        case SDLK_s:
          transform->velocity.y = 1;
          break;
        case SDLK_a:
          transform->velocity.x = -1;
          break;
        case SDLK_d:
          transform->velocity.x = 1;
          break;
        default:
          break;
      }
    }
    if (Game::instance().event.type == SDL_KEYUP) {
      switch (Game::instance().event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = 0;
          break;
        case SDLK_s:
          transform->velocity.y = 0;
          break;
        case SDLK_a:
          transform->velocity.x = 0;
          break;
        case SDLK_d:
          transform->velocity.x = 0;
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
