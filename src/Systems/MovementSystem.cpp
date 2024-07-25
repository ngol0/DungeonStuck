#include "MovementSystem.h"

#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../ECS/ECS.h"

#include <spdlog/spdlog.h>

MovementSystem::MovementSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<MovementComponent>();
}

void MovementSystem::Update(float dt)
{
    //update the transform
    for (auto& e : GetSystemEntities())
    {
        TransformComponent* transform = e.GetComponent<TransformComponent>();
        MovementComponent* movement = e.GetComponent<MovementComponent>();

        transform->position += movement->moveDirection * movement->speed * dt;

        //spdlog::info("Position x: " + std::to_string(transform->position.x) + " , y: " + std::to_string(transform->position.y));
    }
}