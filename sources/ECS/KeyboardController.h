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

    if (Game::instance().event.type == SDL_MOUSEBUTTONDOWN) {
      if (Game::instance().event.button.button == SDL_BUTTON_LEFT) {
        auto x = Game::instance().event.button.x;
        auto y = Game::instance().event.button.y;

        entity->getComponent<SpriteComponent>().play(AnimationId::Attack);
        auto pos = entity->getComponent<TransformComponent>().pos ;
        Vector2D velocity = Vector2D{ x, y };
        velocity -= pos;
        velocity /= Vector2D{ 150.f, 150.f };
        Game::instance().assets->createProjectile(
          pos, velocity, 500, 1, pos.angle(Vector2D{ x, y }), "arrow");
      }
    }
    if (Game::instance().event.type == SDL_MOUSEBUTTONUP) {
      if (Game::instance().event.button.button == SDL_BUTTON_LEFT) {
        entity->getComponent<SpriteComponent>().play(AnimationId::Idle);
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
