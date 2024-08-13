#include "PlayerInputSystem.h"
#include "PlayerMovementSystem.h"

#include "../Input/InputManager.h"
#include "../Input/InputData.h"

#include <SDL2/SDL_image.h>

PlayerInputSystem::PlayerInputSystem() {}

void PlayerInputSystem::Init()
{
    ConfigureDefaultInputBindings();
}

void PlayerInputSystem::ConfigureDefaultInputBindings()
{
    auto& inputManager = InputManager::GetInstance();

    //------------------------Movement Input---------------------------//
    auto& moveAction = inputManager.AddAction("MoveAction");

    spdlog::info(moveAction.GetName());

    moveAction.AddKeyInputData(SDLK_UP, glm::vec3(0, -1, 0));
    moveAction.AddKeyInputData(SDLK_RIGHT, glm::vec3(1, 0, 1));
    moveAction.AddKeyInputData(SDLK_DOWN, glm::vec3(0, 1, 2));
    moveAction.AddKeyInputData(SDLK_LEFT, glm::vec3(-1, 0, 3));

    //key
    moveAction.AddKeyInputData(SDLK_w, glm::vec3(0, -1, 0));
    moveAction.AddKeyInputData(SDLK_d, glm::vec3(1, 0, 1));
    moveAction.AddKeyInputData(SDLK_s, glm::vec3(0, 1, 2));
    moveAction.AddKeyInputData(SDLK_a, glm::vec3(-1, 0, 3));

    //input binding
    auto& movementSystem = Registry::GetInstance().GetSystem<PlayerMovementSystem>();
    inputManager.BindAction(moveAction.GetName(), &movementSystem, &PlayerMovementSystem::Move);

    //------------------------Interact Input---------------------------//

    //------------------------Fight Input------------------------------//
}