#include "AssetManager.h"

AssetManager::AssetManager(Manager *m) : manager(m) {}

AssetManager::~AssetManager() {
  std::for_each(textures.begin(), textures.end(),
                [](std::pair<std::string, SDL_Texture *> kvp) {
                  SDL_DestroyTexture(kvp.second);
                });
}

void AssetManager::addTexture(std::string const &id, std::string const &path) {
  textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture *AssetManager::getTexture(std::string const &id) {
  return textures[id];
}
