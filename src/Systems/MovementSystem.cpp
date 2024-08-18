#include "MovementSystem.h"

#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"

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
        auto& transform = e.GetComponent<TransformComponent>();
        auto& movement = e.GetComponent<MovementComponent>();

        //transform.position += movement.moveDirection * movement.speed * dt;
    }
}