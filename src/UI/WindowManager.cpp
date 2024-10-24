
#include "WindowManager.h"
#include "GameWindow.h"
#include "PauseWindow.h"

#include "../Systems/HUDSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------Window State------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
GameWindow WindowState::vitals;
PauseWindow WindowState::pause;

void Window::OnEnter()
{
    for (auto &e : m_entitites)
    {
        auto* uiPtr = e.GetComponentPtr<UIComponent>();
        if (uiPtr != nullptr) e.GetComponent<UIComponent>().isActive = true;

        auto* textPtr = e.GetComponentPtr<TextComponent>();
        if (textPtr != nullptr) textPtr->isActive = true;
    }
}

void Window::OnExit()
{
    for (auto &e : m_entitites)
    {
        auto* uiPtr = e.GetComponentPtr<UIComponent>();
        if (uiPtr != nullptr) e.GetComponent<UIComponent>().isActive = false;

        auto* textPtr = e.GetComponentPtr<TextComponent>();
        if (textPtr != nullptr) textPtr->isActive = false;
    }
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------Window Manager----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
WindowManager::WindowManager() : m_current_window(nullptr) {}

void WindowManager::Init(SDL_Renderer* renderer)
{
    WindowState::vitals.Init();
    WindowState::pause.Init();

	// set the first window
	SetWindow(WindowState::vitals);

    m_renderer = renderer;

    // add hud system
    Registry::GetInstance().AddSystem<HUDSystem>();
    Registry::GetInstance().AddSystem<RenderTextSystem>();
}

void WindowManager::SetWindow(Window& window)
{
	//do something before changing to the new one
	if (m_current_window != nullptr)
	{
		m_current_window->OnExit();
	}
	m_current_window = &window;  //pointing to the new one
	m_current_window->OnEnter(); //do something right after switching
}

void WindowManager::Update(float deltaTime)
{
	m_current_window->Update(deltaTime);
}

void WindowManager::Render()
{
    //call hud render system and text render system
    Registry::GetInstance().GetSystem<HUDSystem>().Render(m_renderer);
    Registry::GetInstance().GetSystem<RenderTextSystem>().Render(m_renderer);
}

// called when R is pressed
void WindowManager::Restart()
{
	
}

WindowManager& WindowManager::GetInstance()
{
	static WindowManager manager;
	return manager;
}