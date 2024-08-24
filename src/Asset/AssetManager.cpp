#include "AssetManager.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

#include "../ECS/ECS.h"
#include "../Game/EntityFactory.h"

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

void AssetManager::OpenMapFile(const char* filename)
{
    m_input.open(filename);
    if (!m_input.is_open())
    {
        spdlog::error("Failed to open map file");
        return;
    }

    ReadMapFile();
    m_input.close();
}

void AssetManager::ReadMapFile()
{
    //Read map info here
    std::string line;

    while (std::getline(m_input, line))
    {
        std::istringstream iss(line);
        std::string first, second;

        //skip the first 2 strings
        iss >> first >> second;

        //read the rest
        //first 2 numbers is size
        glm::vec2 size;
        iss >> size.x >> size.y;

        //next 2 is src rect x & y
        glm::vec2 srcRect;
        iss >> srcRect.x >> srcRect.y;

        //rotation
        float rotation;
        iss >> rotation;

        //position (x, y)
        glm::vec2 pos;
        iss >> pos.x >> pos.y;

        //scale (2 numbers)
        glm::vec2 scale;
        iss >> scale.x >> scale.y;

        //offset
        glm::vec2 offset;
        iss >> offset.x >> offset.y;

        //Create Entity and Component
        EntityFactory::CreateTile(size, srcRect, pos, rotation, scale);
    }
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
