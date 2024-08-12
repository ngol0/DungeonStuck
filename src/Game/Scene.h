#ifndef SCENE_H
#define SCENE_H

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
};

#endif