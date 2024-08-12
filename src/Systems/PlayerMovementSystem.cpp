#include "PlayerMovementSystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PlayerInputComponent.h"

PlayerMovementSystem::PlayerMovementSystem()
{
    RequireComponent<PlayerInputComponent>();
}

void PlayerMovementSystem::Move(glm::vec2& value)
{
    for (auto& e : GetSystemEntities())
    {
        auto& movement = e.GetComponent<MovementComponent>();
        movement.moveDirection = value;
    }
}