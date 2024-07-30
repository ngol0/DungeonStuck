#ifndef SCENE_H
#define SCENE_H

#include "../Entity/EntityFactory.h"

struct SDL_Renderer;

class Scene
{
private:
    Registry m_registry;
    SDL_Renderer* m_renderer;

public:
    void Init(SDL_Renderer* renderer);
    void Update(float deltaTime);
    void Render();
    void Shutdown();
};

#endif