#ifndef SCENE_H
#define SCENE_H

#include "../Entity/EntityFactory.h"

class Scene
{
private:
    Registry registry;

public:
    void Init();
    void Update(float deltaTime);
    void Render();
    void Shutdown();
};

#endif