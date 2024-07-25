#ifndef SCENE_H
#define SCENE_H

#include "../Entity/EntityFactory.h"

struct SDL_Renderer;

class Scene
{
private:
    Registry registry;

public:
    void Init();
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Shutdown();
};

#endif