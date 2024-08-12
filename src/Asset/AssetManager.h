#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

namespace SpriteId
{
	const static std::string TANK = "tank";
    const static std::string CHOPPER = "chopper";
}

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
    void LoadTextureAsset(SDL_Renderer* renderer);
    void AddSprite(SDL_Renderer* renderer, const std::string& id, const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& id) 
    { 
        return spriteMap[id]; 
    }

    //singleton
    static AssetManager& GetInstance();
};

#endif