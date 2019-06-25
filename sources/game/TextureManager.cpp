#include "TextureManager.h"
#include <map>

SDL_Texture*
TextureManager::loadTexture(std::string const& filename)
{

  SDL_Surface* surface = IMG_Load(filename.data());
  SDL_Texture* tex =
    SDL_CreateTextureFromSurface(Game::instance().getRenderer(), surface);

  SDL_FreeSurface(surface);

  return tex;
}

void
TextureManager::draw(SDL_Texture* tex,
                     SDL_Rect src,
                     SDL_Rect dest,
                     SDL_RendererFlip flipped,
                     double angle)
{
  SDL_RenderCopyEx(
    Game::instance().getRenderer(), tex, &src, &dest, angle, NULL, flipped);
}
