#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>

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

    void LoadTextureAsset();

    static SDL_Rect camera;
};

#endif