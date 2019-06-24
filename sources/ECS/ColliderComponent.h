#pragma once
#include "AssetManager.h"
#include "ECS.h"
#include "Game.h"
#include "SDL.h"
#include "TransformComponent.h"
#include <string>

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  int scale = 1;

  TransformComponent* transform;

  ColliderComponent(std::string const& name)
    : tag(name)
  {}

  ColliderComponent(std::string const& name, int x, int y, int size)
    : tag(name)
  {
    collider.x = x;
    collider.y = y;
    collider.h = collider.w = size;
  }

  ColliderComponent(std::string const& name, int x, int y, int size, int sc)
    : tag(name)
    , scale(sc)
  {
    collider.x = x;
    collider.y = y;
    collider.h = collider.w = size;
  }

  void init() override
  {
    if (!entity->hasComponent<TransformComponent>()) {
      transform = &entity->addComponent<TransformComponent>(
        Vector2D{ collider.x, collider.y },
        Vector2D{ 0, 0 },
        collider.w,
        collider.h,
        scale);
    } else {
      transform = &entity->getComponent<TransformComponent>();
    }
  }

  void update() override
  {
    if (tag != "terrain") {
      collider.w = transform->width * transform->scale;
      collider.h = transform->height * transform->scale;
    }
    collider.x = static_cast<int>(transform->pos.x);
    collider.y = static_cast<int>(transform->pos.y);
  }
};
