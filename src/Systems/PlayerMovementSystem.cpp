#include "PlayerMovementSystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerInputComponent.h"

PlayerMovementSystem::PlayerMovementSystem()
{
    RequireComponent<PlayerInputComponent>();
}

void PlayerMovementSystem::Move(glm::vec3& value)
{
    for (auto& e : GetSystemEntities())
    {
        auto& movement = e.GetComponent<MovementComponent>();
        auto& sprite = e.GetComponent<SpriteComponent>();

        movement.speed = 50.f;
        movement.moveDirection = glm::vec2(value.x, value.y);
        sprite.srcRect.y = sprite.srcRect.h * value.z;
    }
}