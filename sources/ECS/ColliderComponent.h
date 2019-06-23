#pragma once
#include "AssetManager.h"
#include "ECS.h"
#include "Game.h"
#include "SDL.h"
#include "TransformComponent.h"
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;
  std::string tag;

  SDL_Texture *tex;
  SDL_Rect src;
  SDL_Rect dst;

  TransformComponent *transform;

  ColliderComponent(std::string const &name) : tag(name) {}

  ColliderComponent(std::string const &name, int x, int y, int size)
      : tag(name) {
    collider.x = x;
    collider.y = y;
    collider.h = collider.w = size;
  }

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      transform = &entity->addComponent<TransformComponent>();
    } else {
      transform = &entity->getComponent<TransformComponent>();
    }

    entity->addGroup(Game::GroupLabels::Colliders);

    tex = Game::instance().assets->getTexture("collider");
    src = {0, 0, 32, 32};
    dst = {collider.x, collider.y, collider.w, collider.h};
  }

  void update() override {
    if (tag != "terrain") {
      collider.x = static_cast<int>(transform->pos.x);
      collider.y = static_cast<int>(transform->pos.y);
      collider.w = transform->width * transform->scale;
      collider.h = transform->height * transform->scale;
    }

    dst.x = static_cast<int>(collider.x - Game::instance().camera.x);
    dst.y = static_cast<int>(collider.x - Game::instance().camera.y);
  }

  void draw() override { TextureManager::draw(tex, src, dst); }
};
