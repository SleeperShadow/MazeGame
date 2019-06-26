#include "Collision.h"
#include "ColliderComponent.h"
#include <algorithm>

#include <iostream>

bool
Collision::AABB(SDL_Rect const& a, SDL_Rect const& b)
{
  // could simply use the method provided by SDL, but this is more fun I guess
  if (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y)
    return true;

  return false;
}

bool
Collision::AABB(ColliderComponent const& a, ColliderComponent const& b)
{
  if (AABB(a.collider, b.collider)) {
    return true;
  }
  return false;
}
