#pragma once

#include "ColliderComponent.h"
#include "ECS.h"
#include "MapSite.h"
#include "TileComponent.h"

class WallComponent : public Component
{
public:
  TileComponent* tile;
  ColliderComponent* collider;
  MapSite* owner;

  WallComponent(MapSite* o)
    : owner(o)
  {}

  void init() override
  {
    tile = &entity->getComponent<TileComponent>();
    entity->addComponent<ColliderComponent>(
      "wall", tile->dst.x, tile->dst.y, tile->dst.w);
    entity->addGroup(Game::GroupLabels::Walls);
  }

  void collide() const { owner->enter(); }
};
