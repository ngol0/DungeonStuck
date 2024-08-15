#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "../Input/InputManager.h"

Game::Game()
{
    b_running = false;
    spdlog::info("Game Created!");

    m_window_height = 600;
    m_window_width = 800;
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
        m_window_width,
        m_window_height,
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

            // emit key pressed event
            InputManager::GetInstance().Execute(e.key.keysym.sym);
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
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // render game objects
    m_scene.Render();

    // ImGui::ShowDemoWindow();
    // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    // {
    //     static float f = 0.0f;
    //     static int counter = 0;

    //     ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    //     ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
    //     ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
    //     ImGui::Checkbox("Another Window", &show_another_window);

    //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
    //     ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

    //     if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
    //         counter++;
    //     ImGui::SameLine();
    //     ImGui::Text("counter = %d", counter);

    //     //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    //     ImGui::End();
    // }

    // // 3. Show another simple window.
    // if (show_another_window)
    // {
    //     ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    //     ImGui::Text("Hello from another window!");
    //     if (ImGui::Button("Close Me"))
    //         show_another_window = false;
    //     ImGui::End();
    // }

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