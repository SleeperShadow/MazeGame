#pragma once

enum AnimationId : unsigned char
{
  Idle = 0,
  Move,
  Attack,
  Death,
};

struct Animation
{
  int frames;
  int speed;

  Animation() = default;
  Animation(int f, int s)
    : frames(f)
    , speed(s)
  {}
};
