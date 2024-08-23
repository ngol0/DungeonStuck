#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <fstream>

struct SDL_Renderer;
struct SDL_Texture;

class AssetManager
{
private:
    std::map<std::string, SDL_Texture*> spriteMap;
    std::ifstream m_input;

    void ReadMapFile();

public:
    AssetManager() {}
    AssetManager(const AssetManager&) = delete; //avoid copy constructor
    ~AssetManager();

    void ClearAsset();

    void OpenMapFile(const char* filename);

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