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
  int width;
  int height;

  Animation() = default;
  Animation(int f, int s, int w, int h)
    : frames(f)
    , speed(s)
    , width(w)
    , height(h)
  {}
};
