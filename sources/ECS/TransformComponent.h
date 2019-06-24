#pragma once
#include "ECS.h"
#include "Vector2d.h"

class TransformComponent : public Component
{
public:
  Vector2D pos;
  Vector2D velocity;
  int speed = 3;
  int height = 32;
  int width = 32;
  int scale = 1;

  TransformComponent()
  {
    pos = pos.zero();
    velocity = velocity.zero();
  }

  TransformComponent(Vector2D p, Vector2D v, int w, int h, int sc, int sp)
    : pos(p)
    , velocity(v)
    , width(w)
    , height(h)
    , scale(sc)
    , speed(sp)
  {}

  TransformComponent(int sc)
    : scale(sc)
  {
    pos = pos.zero();
    velocity = velocity.zero();
  }

  TransformComponent(float x, float y, int w, int h, int _scale)
  {
    pos.x = x;
    pos.y = y;
    width = w;
    height = h;
    this->scale = _scale;
    velocity.zero();
  }

  TransformComponent(Vector2D p, Vector2D v, int w, int h, int _scale)
    : TransformComponent(p, v, w, h, _scale, 3)
  {}

  void update() override
  {
    pos.x += static_cast<int>(velocity.x * speed);
    pos.y += static_cast<int>(velocity.y * speed);
  }

  void setPos(float _x, float _y)
  {
    pos.x = _x;
    pos.y = _y;
  }
};
