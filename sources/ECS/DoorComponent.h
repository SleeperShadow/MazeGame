#pragma once
#include "Door.h"
#include "WallComponent.h"

class DoorComponent : public Component
{
public:
  TileComponent* tile;
  ColliderComponent* collider;
  Door* owner;

  int doorFrame = 0;

  DoorComponent(Door* o)
    : owner(o)
  {}

  void init() override
  {
    tile = &entity->getComponent<TileComponent>();
    collider = &entity->addComponent<ColliderComponent>(
      "door", tile->dst.x, tile->dst.y, tile->dst.w);
    entity->addGroup(Game::GroupLabels::Doors);
  }

  void update() override
  {
    if (owner->opened() && doorFrame < 4) {
      tile->src.x = tile->src.w * static_cast<int>((SDL_GetTicks() / 1000) % 5);
      tile->src.y = 64;
      ++doorFrame;
    }
  }

  void collide() { owner->enter(); }
};
