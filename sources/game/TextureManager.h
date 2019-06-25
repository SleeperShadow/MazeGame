#pragma once
#include "Game.h"
#include <string>

class TextureManager
{
public:
  static SDL_Texture* loadTexture(std::string const& filename);
  static void draw(SDL_Texture* tex,
                   SDL_Rect src,
                   SDL_Rect dest,
                   SDL_RendererFlip flipped = SDL_FLIP_NONE,
                   double angle = 0.f);
};
