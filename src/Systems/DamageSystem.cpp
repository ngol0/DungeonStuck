#include "DamageSystem.h"
#include "../Components/HealthComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"

#include "../ECS/ECS.h"

DamageSystem::DamageSystem()
{
    RequireComponent<HealthComponent>();
}

void DamageSystem::Init()
{
    RegisterToEvent();
}

void DamageSystem::RegisterToEvent()
{
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &DamageSystem::OnCollisionHappen);
}

void DamageSystem::DamageTakenBy(Entity& victim, float damageAmount, CollisionData& data)
{
    auto& health = victim.GetComponent<HealthComponent>();
    health.healthAmount -= damageAmount;
    if (health.healthAmount <= 0.f)
    {
        victim.Destroy();
        EventManager::GetInstance().Notify(EventType::OnEntityDestroy, data);
    }
}

void DamageSystem::OnCollisionHappen(CollisionData& data)
{
    auto& collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto& collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::ENEMY)
    {
        Entity player(data.collisionPair.first);
        DamageTakenBy(player, 100, data);
    }
    else if (collider1.tag == Tag::ENEMY && collider2.tag == Tag::PLAYER)
    {
        Entity player(data.collisionPair.second);
        DamageTakenBy(player, 100, data);
    }
    else if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::ENEMY_BULLET)
    {

    }
    else if (collider1.tag == Tag::ENEMY_BULLET && collider2.tag ==  Tag::PLAYER)
    {

    }
    else if (collider1.tag == Tag::PLAYER_BULLET && collider2.tag ==  Tag::ENEMY)
    {

    }
    else if (collider1.tag == Tag::ENEMY && collider2.tag ==  Tag::PLAYER_BULLET)
    {

    }
}