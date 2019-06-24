#include "AssetManager.h"
#include "Components.h"

std::map<std::string, SDL_Texture*> textures;

AssetManager::AssetManager(Manager* m)
  : manager(m)
{}

void
AssetManager::createProjectile(Vector2D pos,
                               Vector2D vel,
                               int range,
                               int speed,
                               std::string const& texid)
{
  auto& projectile = manager->addEntity();
  projectile.addComponent<TransformComponent>(pos, vel, 32, 32, 2);
  projectile.addComponent<SpriteComponent>(texid, false);
  projectile.addComponent<Projectile>(range, speed);
  projectile.addComponent<ColliderComponent>("projectile");
  projectile.addGroup(Game::GroupLabels::Projectiles);
}

void
AssetManager::addTexture(std::string const& id, std::string const& path)
{
  textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture*
AssetManager::getTexture(std::string const& id)
{
  return textures[id];
}

void
AssetManager::cleanup()
{
  std::for_each(textures.begin(),
                textures.end(),
                [](std::pair<std::string, SDL_Texture*> kvp) {
                  SDL_DestroyTexture(kvp.second);
                });
}
