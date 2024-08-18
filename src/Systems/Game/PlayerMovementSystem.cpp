#include "PlayerMovementSystem.h"

#include "../../Components/MovementComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"

#include "../../Input/InputManager.h"

PlayerMovementSystem::PlayerMovementSystem()
{
    RequireComponent<PlayerInputComponent>();
    RequireComponent<TransformComponent>();
}

void PlayerMovementSystem::Move(glm::vec3& value, float dt)
{
    for (auto& e : GetSystemEntities())
    {
        auto& movement = e.GetComponent<MovementComponent>();
        auto& sprite = e.GetComponent<SpriteComponent>();
        auto& transform = e.GetComponent<TransformComponent>();
        
        movement.moveDirection = glm::vec2(value.x, value.y);
        sprite.srcRect.y = sprite.srcRect.h * value.z;

        transform.position += movement.moveDirection * movement.speed * dt;
    }
}