#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"

#include "../../Input/InputManager.h"

#include <SDL2/SDL.h>

PlayerInputSystem::PlayerInputSystem() 
{
    
}

void PlayerInputSystem::Init()
{
    ConfigureDefaultInputBindings();
}

void PlayerInputSystem::ConfigureDefaultInputBindings()
{
    auto& inputManager = InputManager::GetInstance();

    //------------------------Movement Input---------------------------//
    InputAction<glm::vec3> moveAction{"Move"};
    moveAction.AddKeyInputData("MoveLeft", SDLK_a, glm::vec3(-1, 0, 3));
    moveAction.AddKeyInputData("MoveRight", SDLK_d, glm::vec3(1, 0, 1));
    moveAction.AddKeyInputData("MoveDown", SDLK_s, glm::vec3(0, 1, 2));
    moveAction.AddKeyInputData("MoveUp", SDLK_w, glm::vec3(0, -1, 0)); 

    //---Input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerMovementSystem>();
    
    //key pressed
    for (auto& data : moveAction.m_inputData)
    {
        inputManager.BindKeyPressed(data, &movementSystem, &PlayerMovementSystem::Move);
    }

    //------------------------Interact Input---------------------------//


    //------------------------Fight Input------------------------------//

    
}

