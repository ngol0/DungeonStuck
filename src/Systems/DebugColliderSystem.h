#ifndef DEBUGCOLLIDERSYSTEM_H
#define DEBUGCOLLIDERSYSTEM_H

#include "../ECS/ECS.h"

struct SDL_Renderer;

class DebugColliderSystem : public System
{
public:
    DebugColliderSystem();

    void Render(SDL_Renderer* renderer) override;
};

#endif