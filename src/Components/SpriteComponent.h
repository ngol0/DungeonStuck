#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Asset/AssetManager.h"

namespace SpriteId
{
	const static std::string TANK = "tank";
    const static std::string CHOPPER = "chopper";
}

struct SpriteComponent
{
    SDL_Texture* texture{nullptr};
    SDL_Rect srcRect;

    std::string assetId;
    int width;
    int height;

    SpriteComponent(const std::string& id = "", int srcRectX = 0, int srcRectY = 0) : assetId(id)
    {
        if (id != "")
        {
            texture = AssetManager::GetInstance().GetTexture(id);
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);

            srcRect = {srcRectX, srcRectY, width, height};
        }
    }
};

#endif
