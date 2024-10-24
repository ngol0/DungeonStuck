#include "GameWindow.h"
#include "PauseWindow.h"
#include "../Game/EntityFactory.h"
#include "../Components/InventoryComponent.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"

void GameWindow::Init()
{
    // player health ui
    Entity healthUI = EntityFactory::CreateHealthUI(glm::vec2{5.f, 5.f});
    m_entitites.push_back(healthUI);

    // game UI - inventory UI
    for (int i = 0; i < InventoryComponent::NUM_OF_SLOT; ++i)
    {
        //---top right corner
        // EntityFactory::CreateInventorySlotUI(glm::vec2{750.f - i * 50.f, 10.f});
        // EntityFactory::CreateInventoryItemUI(glm::vec2{760.f - i * 50.f, 18.f}, ItemType::NONE, i);

        //--bottom left corner
        Entity inven = EntityFactory::CreateInventorySlotUI(glm::vec2{20 + i * 50.f, 533.f});
        Entity item = EntityFactory::CreateInventoryItemUI(glm::vec2{30.f + i * 50.f, 540.f}, ItemType::NONE, i);

        m_entitites.push_back(inven);
        m_entitites.push_back(item);
    }

    // listen to input event
    EventManager::GetInstance().Register<KeyPressedEventData>(EventType::OnKeyPressed, this, &GameWindow::OnKeyPressed);
}

void GameWindow::OnEnter()
{
    Window::OnEnter();
}

void GameWindow::OnExit()
{
    Window::OnExit();
}

void GameWindow::OnKeyPressed(KeyPressedEventData &data)
{
    if (data.key == SDLK_p)
    {
        WindowManager::GetInstance().SetWindow(WindowState::pause);
    }
}

void GameWindow::Update(float dt)
{
}