#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"
#include "../RenderSystem.h"

#include "../../Input/InputManager.h"

#include <SDL2/SDL.h>

PlayerInputSystem::PlayerInputSystem() 
{
    
}

void PlayerInputSystem::Init()
{
    ConfigDefaultInputBindings();
}

void PlayerInputSystem::ConfigDefaultInputBindings()
{
    auto& inputManager = InputManager::GetInstance();

    //------------------------Movement Input---------------------------//
    InputAction<glm::vec3> moveAction;
    moveAction.AddKeyInputData("MoveLeft", SDLK_a, glm::vec3(-1, 0, 1));
    moveAction.AddKeyInputData("MoveRight", SDLK_d, glm::vec3(1, 0, 3));
    moveAction.AddKeyInputData("MoveDown", SDLK_s, glm::vec3(0, 1, 3)); //1 or 3?
    moveAction.AddKeyInputData("MoveUp", SDLK_w, glm::vec3(0, -1, 3)); //1 or 3?

    //---Input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerMovementSystem>();
    
    //key pressed
    for (auto& data : moveAction.m_inputData)
    {
        inputManager.BindKeyPressed(data, &movementSystem, &PlayerMovementSystem::Move);
    }

    //------------------------Interact Input---------------------------//


    //------------------------Fight Input------------------------------//
    

    //------------------------Debug Input------------------------------//
    InputData<int> inputData("Debugging", SDLK_0, 0);
    auto& renderSystem = Registry::GetInstance().GetSystem<RenderSystem>();
    inputManager.BindKeyDown(inputData, &renderSystem, &RenderSystem::OnDebug);    
}

