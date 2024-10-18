#include "RenderTextSystem.h"

#include "../Asset/AssetManager.h"
#include "../ECS/ECS.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Scene.h"

#include <SDL2/SDL.h>

RenderTextSystem::RenderTextSystem()
{
    RequireComponent<TextComponent>();
    RequireComponent<TransformComponent>();
}

void RenderTextSystem::Render(SDL_Renderer *renderer)
{
    for (auto entity : GetSystemEntities())
    {
        auto& textLabel = entity.GetComponent<TextComponent>();
        //auto& transform = entity.GetComponent<TransformComponent>();

        SDL_Surface *surface = TTF_RenderText_Blended
        (
            AssetManager::GetInstance().GetFont(textLabel.id),
            textLabel.text.c_str(),
            textLabel.color
        );

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        int labelWidth = 0;
        int labelHeight = 0;

        SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

        SDL_Rect dstRect = {
            static_cast<int>(textLabel.position.x - (textLabel.isFixed ? 0 : Scene::camera.x)),
            static_cast<int>(textLabel.position.y - (textLabel.isFixed ? 0 : Scene::camera.x)),
            labelWidth,
            labelHeight};

        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture);
    }
}