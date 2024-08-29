#include "WeaponSpawningSystem.h"

#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Events/EventManager.h"
#include "../../Events/EventData.h"
#include "../../Global/WeaponData.h"

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
        
        //todo: get weapon type from inventory component
        AttackData spawnData(transform.position, WeaponType::BASIC);

        // call an event for attack system to listen
        // create a basic weapon
        EventManager::GetInstance().Notify<AttackData>(EventType::OnAttack, spawnData);
    }
}