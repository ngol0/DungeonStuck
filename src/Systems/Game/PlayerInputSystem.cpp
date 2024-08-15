#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"

#include "../../Input/InputManager.h"

#include <SDL2/SDL.h>

PlayerInputSystem::PlayerInputSystem() 
{
    moveAction.id = "Move";
}

void PlayerInputSystem::Init()
{
    ConfigureDefaultInputBindings();
}

void PlayerInputSystem::ConfigureDefaultInputBindings()
{
    auto& inputManager = InputManager::GetInstance();

    //------------------------Movement Input---------------------------//
    moveAction.AddKeyInputData("MoveLeft", SDLK_LEFT, glm::vec3(-1, 0, 3));
    moveAction.AddKeyInputData("MoveDown", SDLK_DOWN, glm::vec3(0, 1, 2));
    moveAction.AddKeyInputData("MoveRight", SDLK_RIGHT, glm::vec3(1, 0, 1));
    moveAction.AddKeyInputData("MoveUp", SDLK_UP, glm::vec3(0, -1, 0)); 

    //input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerMovementSystem>();

    for (auto& data : moveAction.m_inputData)
    {
        inputManager.BindKey(data, &movementSystem, &PlayerMovementSystem::Move);
    }

    //------------------------Interact Input---------------------------//


    //------------------------Fight Input------------------------------//

    
}

