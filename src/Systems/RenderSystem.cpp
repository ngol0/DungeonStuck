#include "RenderSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/PathNodeComponent.h"
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
    Scene::isDebugging = !Scene::isDebugging;
}

void RenderSystem::Render(SDL_Renderer *renderer)
{
    struct RenderableEntity
    {
        TransformComponent transformComponent;
        SpriteComponent spriteComponent;
        BoxColliderComponent* boxColliderComponent = nullptr;
        PathNodeComponent* pathNodeComponent = nullptr;
    };

    std::vector<RenderableEntity> renderableEntities;

    for (auto& entity : GetSystemEntities())
    {
        RenderableEntity renderableEntity;
        renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
        renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();

        if (entity.HasComponent<BoxColliderComponent>())
            renderableEntity.boxColliderComponent = entity.GetComponentPtr<BoxColliderComponent>();

        if (entity.HasComponent<PathNodeComponent>())
            renderableEntity.pathNodeComponent = entity.GetComponentPtr<PathNodeComponent>();

        // only render entities that are in the camera view
        bool outsideCameraView = 
        (
            renderableEntity.transformComponent.position.x + renderableEntity.spriteComponent.width * renderableEntity.transformComponent.scale.x < Scene::camera.x ||
            renderableEntity.transformComponent.position.x > Scene::camera.x + Scene::camera.w ||
            renderableEntity.transformComponent.position.y + renderableEntity.spriteComponent.height * renderableEntity.transformComponent.scale.y < Scene::camera.y ||
            renderableEntity.transformComponent.position.y > Scene::camera.y + Scene::camera.h
        );

        if (outsideCameraView)
        {
            continue;
        }

        renderableEntities.emplace_back(renderableEntity);
    }

    std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity &a, const RenderableEntity &b)
              { return a.spriteComponent.zIndex < b.spriteComponent.zIndex; });
            
    for (auto &e : renderableEntities)
    {
        TransformComponent &transform = e.transformComponent;
        SpriteComponent &sprite = e.spriteComponent;

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

        //------------------------------------RENDER DEBUG COLLIDER--------------------------------//
        if (Scene::isDebugging)
        {
            BoxColliderComponent *collider = e.boxColliderComponent;

            if (collider != nullptr)
            {
                SDL_Rect boxRect = {
                static_cast<int>(transform.position.x + collider->offset.x - Scene::camera.x),
                static_cast<int>(transform.position.y + collider->offset.y - Scene::camera.y),
                static_cast<int>(collider->width),
                static_cast<int>(collider->height)};

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &boxRect);
            }

        //------------------------------------RENDER DEBUG GRID POS--------------------------------//
            PathNodeComponent *pathNode = e.pathNodeComponent;

            if (pathNode == nullptr) continue;

            SDL_Rect pathNodeRect = {
                static_cast<int>(Utils::GridToWordPos(pathNode->gridPos).x - Scene::camera.x),
                static_cast<int>(Utils::GridToWordPos(pathNode->gridPos).y - Scene::camera.y),
                static_cast<int>(10),
                static_cast<int>(10)};

            SDL_SetRenderDrawColor(renderer, pathNode->r, pathNode->g, pathNode->b, 255);
            SDL_RenderDrawRect(renderer, &pathNodeRect);
        }
    }
}