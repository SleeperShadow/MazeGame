#pragma once
#include "KeyboardController.h"
#include <cmath>

class MouseController : public Component
{
public:
  TransformComponent* transform;
  SpriteComponent* sprite;

  void init() override
  {
    sprite = &entity->getComponent<SpriteComponent>();
    transform = &entity->getComponent<TransformComponent>();
  }

  void update() override
  {
    if (Game::instance().event.type == SDL_MOUSEBUTTONDOWN) {
      if (Game::instance().event.button.button == SDL_BUTTON_LEFT) {
        sprite->play(AnimationId::Attack);
      }
    }
    if (Game::instance().event.type == SDL_MOUSEBUTTONUP) {
      if (Game::instance().event.button.button == SDL_BUTTON_LEFT) {
        sprite->play(AnimationId::Idle);

        auto x = Game::instance().event.button.x + Game::instance().camera.x;
        auto y = Game::instance().event.button.y + Game::instance().camera.y;

        Game::instance().assets->createProjectile(
          transform->pos, Vector2D{x,y}, 500, 3, transform->pos.angle(Vector2D{x,y}) - 45, "arrow");
      }
    }
  }
};
