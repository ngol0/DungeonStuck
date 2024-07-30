#include "RenderSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Global/AssetManager.h"

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
        TransformComponent& transform = e.GetComponent<TransformComponent>();
        SpriteComponent& sprite = e.GetComponent<SpriteComponent>();

        SDL_Rect srcRect = sprite.srcRect;

        SDL_Rect dsRect = { 
            static_cast<int>(transform.position.x), 
            static_cast<int>(transform.position.y), 
            static_cast<int>(transform.scale.x * sprite.width), 
            static_cast<int>(transform.scale.y * sprite.height) 
        };
        
        SDL_RenderCopyEx(
            renderer, 
            AssetManager::GetInstance().GetTexture(sprite.assetId), //todo: ??
            &srcRect,
            &dsRect,
            transform.rotation,
            NULL,
            SDL_FLIP_NONE
        );
    }
}