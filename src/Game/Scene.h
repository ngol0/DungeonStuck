#ifndef SCENE_H
#define SCENE_H

#include "../Entity/EntityFactory.h"
#include "../Events/EventManager.h"

struct SDL_Renderer;

class Scene
{
private:
    SDL_Renderer* m_renderer;

public:
    void Init(SDL_Renderer* renderer);
    void Update(float deltaTime);
    void Render();
    void Clear();
};

#endif