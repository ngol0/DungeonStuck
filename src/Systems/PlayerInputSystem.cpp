#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"
#include "../Input/InputManager.h"
#include "../Input/InputData.h"

#include <SDL2/SDL_image.h>

PlayerInputSystem::PlayerInputSystem() {}

void PlayerInputSystem::Init()
{
    // Movement Input
    InputAction<glm::vec3> moveAction;
    moveAction.AddKeyInputData(SDLK_UP, glm::vec3(0, -1, 0));
    moveAction.AddKeyInputData(SDLK_RIGHT, glm::vec3(1, 0, 1));
    moveAction.AddKeyInputData(SDLK_DOWN, glm::vec3(0, 1, 2));
    moveAction.AddKeyInputData(SDLK_LEFT, glm::vec3(-1, 0, 3));

    //input binding
    for (const auto& data : moveAction.GetInputData())
    {
        InputManager::GetInstance().BindKey<glm::vec3>(*data, 
            &Registry::GetInstance().GetSystem<PlayerMovementSystem>(), &PlayerMovementSystem::Move);
    }

    // Interact Input

    // Fight input
}