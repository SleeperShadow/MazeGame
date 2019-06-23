#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(std::string const& texture, int _x, int _y)
	: x(_x), y(_y)
{
	objTex = TextureManager::loadTexture(texture);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	++x;
	++y;

	srcRect.h = 32;
	srcRect.w = 22;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = srcRect.w * 2;
	dstRect.h = srcRect.h * 2;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::instance().getRenderer(), objTex, &srcRect, &dstRect);
}
