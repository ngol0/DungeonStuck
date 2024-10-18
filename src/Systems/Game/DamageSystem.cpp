#include "DamageSystem.h"
#include "../../Components/HealthComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/TransformComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

DamageSystem::DamageSystem()
{
    RequireComponent<HealthComponent>();
}

void DamageSystem::Init()
{
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnCollisionEnter, this, &DamageSystem::OnCollisionHappen);
}

void DamageSystem::DamageTakenBy(Entity& victim, float damageAmount, CollisionEventData& data)
{
    auto& health = victim.GetComponent<HealthComponent>();
    health.healthAmount -= damageAmount;
    if (health.healthAmount <= 0.f)
    {
        EventManager::GetInstance().Notify(EventType::OnEntityDestroy, victim); //for changing the behavior of the victim
        //EventManager::GetInstance().Notify(EventType::OnEntityDestroy, data); //reset the collision status
    }
}

void DamageSystem::OnCollisionHappen(CollisionEventData& data)
{
    auto& collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto& collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    //player: collide with enemy or enemy bullet
    //enemy : collide with player bullet

    //if first is player, second is enemy/enemy bullet > player is victim
    if (collider1.tag == Tag::PLAYER)
    {
        if (collider2.tag == Tag::ENEMY_BULLET || collider2.tag == Tag::ENEMY)
        {
            Entity player(data.collisionPair.first);
            DamageTakenBy(player, 100, data);
            auto& health = player.GetComponent<HealthComponent>();
            EventManager::GetInstance().Notify<HealthData>(EventType::OnHealthChanged, HealthData(health.healthAmount));
        }
    }
    //if second is player, first is enemy/enemy bullet > player is victim
    else if (collider2.tag == Tag::PLAYER)
    {
        if (collider1.tag == Tag::ENEMY_BULLET || collider1.tag == Tag::ENEMY)
        {
            Entity player(data.collisionPair.second);
            DamageTakenBy(player, 100, data);
            auto& health = player.GetComponent<HealthComponent>();
            EventManager::GetInstance().Notify<HealthData>(EventType::OnHealthChanged, HealthData(health.healthAmount));
        }
    }
    //if first is enemy, second is player bullet
    //todo: have a component that holds the data of damage inflicted
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