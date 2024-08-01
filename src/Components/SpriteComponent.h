#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Global/AssetManager.h"

struct SpriteComponent
{
    std::string assetId;
    SDL_Rect srcRect;
    int width;
    int height;

    SpriteComponent(const std::string& id = "", int srcRectX = 0, int srcRectY = 0) : assetId(id)
    {
        auto texture = AssetManager::GetInstance().GetTexture(id);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif