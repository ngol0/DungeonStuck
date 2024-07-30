#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>

struct SpriteComponent
{
    std::string assetId;
    SDL_Rect srcRect;
    int width;
    int height;

    SpriteComponent(const std::string& id = "", int w = 0, int h = 0, int srcRectX = 0, int srcRectY = 0) 
        : assetId(id), width(w), height(h)
    {
        srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif
