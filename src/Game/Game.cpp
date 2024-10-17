#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "../Input/InputManager.h"
#include "../Events/EventManager.h"

int Game::window_height = 600;
int Game::window_width = 800;

Game::Game()
{
    b_running = false;
    spdlog::info("Game Created!");
}

Game::~Game()
{
    spdlog::info("Game Quit!");
}

void Game::InitWindow()
{
    // sdl_init returns 0 when there's no error
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        spdlog::error("Error Init SDL");
        return;
    }

    // create a window
    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Game::window_width,
        Game::window_height,
        SDL_WINDOW_BORDERLESS);

    if (!m_window)
    {
        spdlog::error("Error Create SDL Window");
        return;
    }

    // create sdl renderer
    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        spdlog::error("Error Create SDL Renderer");
        return;
    }

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    b_running = true;

    // ImGUI stuff here: todo: move somewhere else later
    //--For Testing
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer2_Init(m_renderer);
}

void Game::Setup()
{
    m_scene.Init(m_renderer);
}

void Game::Run()
{
    Setup();
    while (b_running)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput()
{
    SDL_Event e; // event handler
    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
        switch (e.type)
        {
        case SDL_QUIT:
            b_running = false;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                b_running = false;
            }
            if (e.key.repeat == 0)
            {
                // emit key pressed event
                InputManager::GetInstance().OnKeyDown(e.key.keysym.sym);
                EventManager::GetInstance().Notify<KeyPressedData>(EventType::OnKeyPressed, KeyPressedData(e.key.keysym.sym));
            }
            break;
        case SDL_KEYUP:
            if (e.key.repeat ==0) 
            {
                InputManager::GetInstance().OnKeyUp(e.key.keysym.sym);
                EventManager::GetInstance().Notify<KeyPressedData>(EventType::OnKeyUp, KeyPressedData(e.key.keysym.sym));
            }
            break;
        }
    }
}

void Game::Update()
{
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - m_last_update_frame) / 1000.0f;

    m_last_update_frame = currentTime;

    // Update System
    m_scene.Update(deltaTime);
    InputManager::GetInstance().Update(deltaTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // render game objects
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    m_scene.Render();
    
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Game::Destroy()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    m_scene.Clear();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}