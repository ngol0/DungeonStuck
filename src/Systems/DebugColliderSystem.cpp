#include "DebugColliderSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

#include <SDL2/SDL.h>

DebugColliderSystem::DebugColliderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

void DebugColliderSystem::Render(SDL_Renderer* renderer)
{
    for (auto& e : GetSystemEntities())
    {
        TransformComponent& transform = e.GetComponent<TransformComponent>();
        BoxColliderComponent& collider = e.GetComponent<BoxColliderComponent>();

        SDL_Rect dsRect = { 
            static_cast<int>(transform.position.x + collider.offset.x), 
            static_cast<int>(transform.position.y + collider.offset.y), 
            static_cast<int>(collider.width), 
            static_cast<int>(collider.height) 
        };
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dsRect);
    }
}