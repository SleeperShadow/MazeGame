#pragma once
#include "Components.h"
#include "ECS.h"
#include "SpriteComponent.h"
#include "TextureManager.h"

class Projectile : public Component
{
public:
  Projectile(int rng, int sp, double a, Vector2D s, Vector2D e)
    : range(rng)
    , speed(sp)
    , distance(0)
    , angle(a)
    , start(s)
    , end(e)
  {}

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
    sprite->angle = angle;
    transform->velocity = end - start;
    transform->velocity.x /= range;
    transform->velocity.x *= speed;
    transform->velocity.y /= range;
    transform->velocity.y *= speed;
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
  Vector2D start;
  Vector2D end;
};
