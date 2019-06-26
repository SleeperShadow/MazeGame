#pragma once
#include "SpriteComponent.h"
#include "ColliderComponent.h"


class HealthComponent : public Component
{
    public:
    int health;
    int maxHealth;
    ColliderComponent* collider = nullptr;


    HealthComponent(int h) : health(h), maxHealth(h)
    {}

    void init() override {
        collider = &entity->getComponent<ColliderComponent>();
    }

    void update() override {
        if(health == 0)
        {
            entity->getComponent<SpriteComponent>().play(AnimationId::Death);
            entity->destroy();
        }
    }

    void draw() override
    {
        SDL_SetRenderDrawColor(Game::instance().getRenderer(), 255, 0 ,0, 255);
        auto pos = collider->collider;
        SDL_Rect rect;
        rect.x = (int)pos.x - Game::instance().camera.x;
        rect.y = (int)pos.y - 8 - Game::instance().camera.y;
        rect.w = collider->collider.w;
        rect.h = 8;

        SDL_RenderDrawRect(Game::instance().getRenderer(), &rect);

        rect.w = static_cast<int>((rect.w * health) / maxHealth);
        SDL_RenderFillRect(Game::instance().getRenderer(), &rect);

        SDL_SetRenderDrawColor(Game::instance().getRenderer(), 0, 0, 0, 255);
    }
};