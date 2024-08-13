#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Scene.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

class Game
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Scene m_scene;

    bool b_running;
    int m_window_width;
    int m_window_height;

    Uint32 m_last_update_frame;

    // Our state
    bool show_demo_window{true};
    bool show_another_window{false};
    ImVec4 clear_color{ImVec4(0.45f, 0.55f, 0.60f, 1.00f)};

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
};

#endif