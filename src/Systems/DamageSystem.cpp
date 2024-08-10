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

    //player: collide with enemy or enemy bullet
    //enemy : collide with player bullet

    //todo: have a component that holds the data of damage inflicted

    //if first is player, second is enemy/enemy bullet > player is victim
    if (collider1.tag == Tag::PLAYER)
    {
        if (collider2.tag == Tag::ENEMY_BULLET || collider2.tag == Tag::ENEMY)
        {
            Entity player(data.collisionPair.first);

            //todo, get the damage inflicted component and get the data for the damage
            DamageTakenBy(player, 100, data);
        }
    }
    //if second is player, first is enemy/enemy bullet > player is victim
    else if (collider2.tag == Tag::PLAYER)
    {
        if (collider1.tag == Tag::ENEMY_BULLET || collider1.tag == Tag::ENEMY)
        {
            Entity player(data.collisionPair.second);
            DamageTakenBy(player, 100, data);
        }
    }
    //if first is enemy, second is player bullet
    else if (collider1.tag == Tag::ENEMY && collider2.tag == Tag::PLAYER_BULLET)
    {
        Entity enemy(data.collisionPair.first);
        DamageTakenBy(enemy, 100, data);
    }
    //if second is enemy, first is player bullet
    else if (collider2.tag == Tag::ENEMY && collider1.tag == Tag::PLAYER_BULLET)
    {
        Entity enemy(data.collisionPair.second);
        DamageTakenBy(enemy, 100, data);
    }
}