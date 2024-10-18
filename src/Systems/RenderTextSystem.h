#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include "../ECS/ECS.h"

struct SDL_Renderer;

class RenderTextSystem : public System
{
public:
    RenderTextSystem();
    void Render(SDL_Renderer* renderer) override;
};

#endif