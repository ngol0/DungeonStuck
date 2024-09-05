#include "PlayerInputSystem.h"
#include "PlayerActionSystem.h"
#include "AttackSpawningSystem.h"
#include "../RenderSystem.h"
#include "../../Global/GlobalDataType.h"

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
    moveAction.AddKeyInputData("MoveLeft", SDLK_LEFT, glm::vec3(-1, 0, 7));
    moveAction.AddKeyInputData("MoveRight", SDLK_RIGHT, glm::vec3(1, 0, 5));
    moveAction.AddKeyInputData("MoveDown", SDLK_DOWN, glm::vec3(0, 1, 4));
    moveAction.AddKeyInputData("MoveUp", SDLK_UP, glm::vec3(0, -1, 6));

    //---Input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerActionSystem>();
    
    //key pressed
    for (auto& data : moveAction.m_inputData)
    {
        inputManager.BindKeyPressed(data, &movementSystem, &PlayerActionSystem::Move);
    }

    //------------------------Interact Input---------------------------//


    //------------------------Fight Input------------------------------//
    //todo: get the inventory system > get the weapon type and pass the weapon type to here
    InputData<int> fightData("Fight", SDLK_x, 1);
    auto& combatSystem = Registry::GetInstance().GetSystem<AttackSpawningSystem>();
    inputManager.BindKeyDown(fightData, &combatSystem, &AttackSpawningSystem::Attack);
    

    //------------------------Debug Input------------------------------//
    InputData<int> inputData("Debugging", SDLK_0, 0);
    auto& renderSystem = Registry::GetInstance().GetSystem<RenderSystem>();
    inputManager.BindKeyDown(inputData, &renderSystem, &RenderSystem::OnDebug);    
}

