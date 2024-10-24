#include "PauseWindow.h"
#include "../Game/EntityFactory.h"
#include "GameWindow.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"
#include "../Components/TextComponent.h"
#include "../Components/SpriteComponent.h"

void PauseWindow::Init()
{
    Entity e = Registry::GetInstance().CreateEntity();
    SDL_Color white = { 255, 255, 255, 255 };
    e.AddComponent<TextComponent>(glm::vec2{300.f}, "PAUSE", SpriteId::OTHER_TEXT, white, true);

    m_entitites.push_back(e);

    // listen to input event
    EventManager::GetInstance().Register<KeyPressedEventData>(EventType::OnKeyPressed, this, &PauseWindow::OnKeyPressed);
}

void PauseWindow::OnEnter()
{
    Window::OnEnter();
}

void PauseWindow::OnExit()
{
    Window::OnExit();
}

void PauseWindow::OnKeyPressed(KeyPressedEventData &data)
{
    if (data.key == SDLK_o)
    {
        WindowManager::GetInstance().SetWindow(WindowState::vitals);
    }
}

void PauseWindow::Update(float dt)
{
}