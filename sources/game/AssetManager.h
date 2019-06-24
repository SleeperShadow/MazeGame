#pragma once
#include "ECS.h"
#include "TextureManager.h"
#include "Vector2d.h"
#include <map>
#include <string>

class AssetManager
{
public:
  AssetManager(Manager* m);

  inline void changeManager(Manager* m) { manager = m; }

  void createProjectile(Vector2D pos,
                        Vector2D vel,
                        int range,
                        int speed,
                        std::string const& texid);

  // textures
  static void addTexture(std::string const& id, std::string const& path);

  static SDL_Texture* getTexture(std::string const& id);

  static void cleanup();

private:
  Manager* manager;
};
