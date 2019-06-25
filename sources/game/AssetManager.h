#pragma once
#include "ECS.h"
#include "TextureManager.h"
#include "Vector2d.h"
#include <map>
#include <string>

class AssetManager
{
public:
  void createProjectile(Vector2D pos,
                        Vector2D vel,
                        int range,
                        int speed,
                        double angle,
                        std::string const& texid);

  // textures
  static void addTexture(std::string const& id, std::string const& path);

  static SDL_Texture* getTexture(std::string const& id);

  static void cleanup();
};
