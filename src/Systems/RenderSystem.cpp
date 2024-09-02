#include "RenderSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Input/InputManager.h"
#include "../Input/InputData.h"

#include <SDL2/SDL.h>

#include "../Game/Scene.h"

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
}

void RenderSystem::OnDebug(int& num)
{
    m_isDebugging = !m_isDebugging;
}

void RenderSystem::Render(SDL_Renderer *renderer)
{
    for (auto &e : GetSystemEntities())
    {
        TransformComponent &transform = e.GetComponent<TransformComponent>();
        SpriteComponent &sprite = e.GetComponent<SpriteComponent>();

        SDL_Rect srcRect = sprite.srcRect;

        SDL_Rect dsRect = {
            static_cast<int>(transform.position.x - Scene::camera.x),
            static_cast<int>(transform.position.y - Scene::camera.y),
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

        //----------------------RENDER DEBUG COLLIDER--------------------------------//
        if (m_isDebugging)
        {
            BoxColliderComponent *collider = e.GetComponentPtr<BoxColliderComponent>();

            if (collider == nullptr)
                continue;
            SDL_Rect boxRect = {
                static_cast<int>(transform.position.x + collider->offset.x - Scene::camera.x),
                static_cast<int>(transform.position.y + collider->offset.y - Scene::camera.y),
                static_cast<int>(collider->width),
                static_cast<int>(collider->height)};

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &boxRect);
        }
    }
}