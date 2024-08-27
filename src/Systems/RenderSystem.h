#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"

struct SDL_Renderer;

class RenderSystem : public System
{
private:
    bool m_isDebugging = false;

public:
    RenderSystem();
    void Render(SDL_Renderer* renderer) override;
    void OnDebug(int& num);
};

#endif