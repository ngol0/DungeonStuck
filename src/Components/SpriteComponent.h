#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Asset/AssetManager.h"

namespace SpriteId
{
	const static std::string TANK = "tank";
    const static std::string PLAYER = "chopper";

    const static std::string MAP = "map";
}

struct SpriteComponent
{
    SDL_Texture* texture{nullptr};
    SDL_Rect srcRect;

    std::string assetId;
    int width;
    int height;

    SpriteComponent(const std::string& id = "", int srcRectX = -1, int srcRectY = -1, int w = 0, int h = 0) : assetId(id)
    {
        if (id != "")
        {
            texture = AssetManager::GetInstance().GetTexture(id);
            if (srcRectX == -1) //if provided no params
            {
                SDL_QueryTexture(texture, NULL, NULL, &width, &height);
            }
            else //else if indicate srcRect pos
            {
                width = w; 
                height = h;
            }
            srcRect = {srcRectX, srcRectY, width, height};
        }
    }
};

#endif
