#include "DamageSystem.h"
#include "../Components/HealthComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"

#include "../ECS/ECS.h"

DamageSystem::DamageSystem()
{
    RequireComponent<BoxColliderComponent>();
}

void DamageSystem::Init()
{
    RegisterToEvent();
}

void DamageSystem::RegisterToEvent()
{
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &DamageSystem::OnCollisionHappen);
}

void DamageSystem::OnPlayerBulletCollideEnemy(int enemyId)
{

}

void DamageSystem::OnEnemyBulletCollidePlayer(int playerId)
{
    
}

void DamageSystem::OnEnemyCollidePlayer(int playerId)
{
    Entity player(playerId);
    Registry::GetInstance().KillEntity(player);
}

void DamageSystem::OnCollisionHappen(CollisionData& data)
{
    //player > enemy, enemy > bullet, player > enemy bullet
    auto& collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto& collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::ENEMY)
    {
        OnEnemyCollidePlayer(data.collisionPair.first);
    }
    else if (collider1.tag == Tag::ENEMY && collider2.tag == Tag::PLAYER)
    {
        OnEnemyCollidePlayer(data.collisionPair.second);
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