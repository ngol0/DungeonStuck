#include "RenderSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

#include <SDL2/SDL.h>

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
}

void RenderSystem::Render(SDL_Renderer* renderer)
{
    for (auto& e : GetSystemEntities())
    {
        TransformComponent* transform = e.GetComponent<TransformComponent>();
        SpriteComponent* sprite = e.GetComponent<SpriteComponent>();

        SDL_Rect obj = { static_cast<int>(transform->position.x), 
            static_cast<int>(transform->position.y), 
            static_cast<int>(transform->scale.x), 
            static_cast<int>(transform->scale.y) };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderFillRect(renderer, &obj);
    }
}