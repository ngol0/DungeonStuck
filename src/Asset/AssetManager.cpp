#include "AssetManager.h"
#include <SDL2/SDL_image.h>
#include <string>

AssetManager::~AssetManager()
{
    ClearAsset();
}

void AssetManager::ClearAsset()
{
    for (auto& pair : spriteMap)
    {
        SDL_DestroyTexture(pair.second);
    }
    spriteMap.clear();
}

void AssetManager::AddSprite(SDL_Renderer* renderer, const std::string& id, const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //free surface
    SDL_FreeSurface(surface);

    //put it in the map
    spriteMap.emplace(id, texture); //insert only, constructs element in-place
}

AssetManager& AssetManager::GetInstance()
{
	static AssetManager manager;
	return manager;
}
