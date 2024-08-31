#include "ProjectileActionSystem.h"
#include "../../Components/WeaponComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/MovementComponent.h"

ProjectileActionSystem::ProjectileActionSystem()
{
    RequireComponent<WeaponComponent>();
}

void ProjectileActionSystem::Init()
{
    
}

void ProjectileActionSystem::Update(float dt)
{
    for (auto &e : GetSystemEntities())
    {
        // Action: move
        auto& transform = e.GetComponent<TransformComponent>();
        auto& movement = e.GetComponent<MovementComponent>();

        //spdlog::info("Weapon move x: " + std::to_string(movement.moveDirection.x));
        transform.position += movement.moveDirection * movement.speed * dt;

        // Action: destroy
        auto& weapon = e.GetComponent<WeaponComponent>();
        weapon.timer += dt;

        if (weapon.timer >= weapon.endTime)
        {
            e.Destroy();
        }
    }
}