#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include "../ECS/ECS.h"

struct SDL_Renderer;

class HUDSystem : public System
{
public:
    HUDSystem();

    void Init() override {};
    void Update(float dt) override {};
    void Render(SDL_Renderer *renderer) override;
};

#endif

