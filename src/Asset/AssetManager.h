#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>

struct SDL_Renderer;
struct SDL_Texture;

class AssetManager
{
private:
    std::map<std::string, SDL_Texture*> spriteMap;

public:
    AssetManager() {}
    AssetManager(const AssetManager&) = delete; //avoid copy constructor
    ~AssetManager();

    void ClearAsset();

    //texture asset
    void AddSprite(SDL_Renderer* renderer, const std::string& id, const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& id) 
    { 
        return spriteMap[id]; 
    }

    //singleton
    static AssetManager& GetInstance();
};

#endif