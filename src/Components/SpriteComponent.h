#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Asset/AssetManager.h"

namespace SpriteId
{
    const static std::string NONE = "none";
    //game
	const static std::string SLIME = "slime";
    const static std::string PLAYER = "player";
    const static std::string MAP = "map";
    const static std::string BASIC_WEAPON = "basic_weapon";
    const static std::string HEALTH_ITEM = "health_item";
    const static std::string STRENGTH_ITEM = "strength_item";
    const static std::string CHEST = "chest";

    //ui
    const static std::string UI_SLOT_INVENTORY = "ui_slot_inventory";

    //text
    const static std::string STANDARD_TEXT = "standard";
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

struct UIComponent
{
    SDL_Texture* texture{nullptr};
    SDL_Rect srcRect;

    std::string assetId;
    int width;
    int height;

    UIComponent(const std::string& id = "", int srcRectX = -1, int srcRectY = -1, int w = 0, int h = 0) : assetId(id)
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
