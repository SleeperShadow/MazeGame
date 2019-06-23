#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
  static bool AABB(SDL_Rect const& a, SDL_Rect const& b);

  static bool AABB(ColliderComponent const& a, ColliderComponent const& b);
};
