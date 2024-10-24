#include "HUDSystem.h"

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"


HUDSystem::HUDSystem()
{
    RequireComponent<UIComponent>();
    RequireComponent<TransformComponent>();
}

void HUDSystem::Render(SDL_Renderer *renderer)
{
    for (auto &e : GetSystemEntities())
    {
        TransformComponent &transform = e.GetComponent<TransformComponent>();
        UIComponent &sprite = e.GetComponent<UIComponent>();

        if (!sprite.isActive) continue;

        SDL_Rect srcRect = sprite.srcRect;

        SDL_Rect dsRect = {
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            static_cast<int>(transform.scale.x * sprite.srcRect.w),
            static_cast<int>(transform.scale.y * sprite.srcRect.h)};

        SDL_RenderCopyEx(
            renderer,
            sprite.texture,
            &srcRect,
            &dsRect,
            transform.rotation,
            NULL,
            SDL_FLIP_NONE);
    }
}