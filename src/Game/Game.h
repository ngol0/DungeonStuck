#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Scene.h"

class Game
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Scene m_scene;

    bool b_running;

    Uint32 m_last_update_frame;

public:
    Game();
    ~Game();

    void InitWindow();
    void Setup();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    static int window_width;
    static int window_height;
};

#endif