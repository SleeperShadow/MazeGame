#include "AssetManager.h"
#include "Components.h"

std::map<std::string, SDL_Texture*> textures;

void
AssetManager::createProjectile(Vector2D pos,
                               Vector2D vel,
                               int range,
                               int speed,
                               double angle,
                               std::string const& texid)
{
  auto& projectile = Game::instance().getManager().addEntity();
  projectile.addComponent<TransformComponent>(pos, vel, 64, 64, 2, speed);
  projectile.addComponent<SpriteComponent>(texid);
  projectile.addComponent<Projectile>(range, speed, angle);
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
