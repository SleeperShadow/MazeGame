#pragma once
#include "ECS.h"
#include "TextureManager.h"
#include "Vector2d.h"
#include <map>
#include <string>

class AssetManager {
public:
  AssetManager(Manager *m);

  ~AssetManager();

  void addTexture(std::string const &id, std::string const &path);

  SDL_Texture *getTexture(std::string const &id);

private:
  Manager *manager;
  std::map<std::string, SDL_Texture *> textures;
};
