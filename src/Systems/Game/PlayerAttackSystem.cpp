#include "PlayerAttackSystem.h"
#include "../../Events/EventManager.h"
#include "../../Components/WeaponComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Events/EventManager.h"
#include "../../Global/WeaponData.h"
#include "../../Game/EntityFactory.h"

PlayerAttackSystem::PlayerAttackSystem()
{
    RequireComponent<WeaponComponent>();
}

void PlayerAttackSystem::Init()
{
    EventManager::GetInstance().Register<AttackData>(EventType::OnAttack, this, &PlayerAttackSystem::Attack);
}

void PlayerAttackSystem::Update(float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &transform = e.GetComponent<TransformComponent>();
        auto &weapon = e.GetComponent<WeaponComponent>();

        transform.position.x += 300.f * dt;
        weapon.timer += dt;

        if (weapon.timer >= weapon.endTime)
        {
            e.Destroy();
        }
    }
}

void PlayerAttackSystem::Attack(AttackData &data)
{
    glm::vec2 spawnPos = glm::vec2(data.position.x + 20.f, data.position.y + 32.f);
    EntityFactory::CreateWeapon(data.weaponType, spawnPos);
}