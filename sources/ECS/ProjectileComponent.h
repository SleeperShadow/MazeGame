#pragma once
#include "Components.h"
#include "ECS.h"
#include "SpriteComponent.h"

class Projectile : public Component
{
public:
  Projectile(int rng, int sp, double a)
    : range(rng)
    , speed(sp)
    , distance(0)
    , angle(a)
  {}

  ~Projectile() {}

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
  }

  void update() override
  {

    distance += speed;
    if (distance > range) {
      entity->destroy();
    } else if ((transform->pos.x >
                Game::instance().camera.x + Game::instance().camera.w) ||
               (transform->pos.x < Game::instance().camera.x) ||
               (transform->pos.y >
                Game::instance().camera.y + Game::instance().camera.h) ||
               (transform->pos.y < Game::instance().camera.y)) {
      entity->destroy();
    }
  }

private:
  TransformComponent* transform;
  SpriteComponent* sprite;

  int range;
  int speed;
  int distance;
  double angle = 0.0;
};
