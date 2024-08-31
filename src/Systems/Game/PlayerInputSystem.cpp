#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"
#include "WeaponSpawningSystem.h"
#include "../RenderSystem.h"
#include "../../Global/WeaponData.h"

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
    moveAction.AddKeyInputData("MoveLeft", SDLK_LEFT, glm::vec3(-1, 0, 1));
    moveAction.AddKeyInputData("MoveRight", SDLK_RIGHT, glm::vec3(1, 0, 3));
    moveAction.AddKeyInputData("MoveDown", SDLK_DOWN, glm::vec3(0, 1, 3));
    moveAction.AddKeyInputData("MoveUp", SDLK_UP, glm::vec3(0, -1, 3));

    //---Input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerMovementSystem>();
    
    //key pressed
    for (auto& data : moveAction.m_inputData)
    {
        inputManager.BindKeyPressed(data, &movementSystem, &PlayerMovementSystem::Move);
    }

    //------------------------Interact Input---------------------------//


    //------------------------Fight Input------------------------------//
    //todo: get the inventory system > get the weapon type and pass the weapon type to here
    InputData<int> fightData("Fight", SDLK_x, 1);
    auto& combatSystem = Registry::GetInstance().GetSystem<WeaponSpawningSystem>();
    inputManager.BindKeyDown(fightData, &combatSystem, &WeaponSpawningSystem::Attack);
    

    //------------------------Debug Input------------------------------//
    InputData<int> inputData("Debugging", SDLK_0, 0);
    auto& renderSystem = Registry::GetInstance().GetSystem<RenderSystem>();
    inputManager.BindKeyDown(inputData, &renderSystem, &RenderSystem::OnDebug);    
}

