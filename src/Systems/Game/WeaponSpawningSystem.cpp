#include "WeaponSpawningSystem.h"

#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/MovementComponent.h"

#include "../../Global/WeaponData.h"
#include "../../Game/EntityFactory.h"

WeaponSpawningSystem::WeaponSpawningSystem()
{
    RequireComponent<PlayerInputComponent>();
}

void WeaponSpawningSystem::Attack(int &weaponType)
{
    // //get entity
    for (auto &e : GetSystemEntities())
    {
        // create weapon spawn pos
        auto &transform = e.GetComponent<TransformComponent>();
        auto &movement = e.GetComponent<MovementComponent>();

        glm::vec2 spawnPos = glm::vec2(transform.position.x + 20.f, transform.position.y + 32.f);
        EntityFactory::CreateWeapon(WeaponType::BASIC, spawnPos, movement.lastDirection);
    }
}