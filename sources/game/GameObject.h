#pragma once
#include "Game.h"
#include <string>

class GameObject
{
public:
	GameObject(std::string const& texture, int x, int y);

	~GameObject();

	void update();
	void render();

private:
	int x;
	int y;

	SDL_Texture* objTex;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
};