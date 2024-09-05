#include "AttackSpawningSystem.h"

#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/MovementComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/AnimationComponent.h"

#include "../../Global/GlobalDataType.h"
#include "../../Game/EntityFactory.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

AttackSpawningSystem::AttackSpawningSystem()
{
    RequireComponent<PlayerInputComponent>();
}

void AttackSpawningSystem::Attack(int &weaponType)
{
    // //get entity
    for (auto &e : GetSystemEntities())
    {
        // create weapon spawn pos
        auto &transform = e.GetComponent<TransformComponent>();
        auto &movement = e.GetComponent<MovementComponent>();
        auto &anim = e.GetComponent<AnimationComponent>();

        // change sprite
        auto &sprite = e.GetComponent<SpriteComponent>();
        anim.isLooping = false;
        anim.endOfSprite = false;
        anim.currentFrame = 0;

        glm::vec2 spawnPos;
        glm::vec2 midPoint = glm::vec2{transform.position.x + 60.f, transform.position.y + 50.f};
        if (movement.lastDirection.x < 0) 
        {
            sprite.srcRect.y = sprite.srcRect.h * 10; // left
            spawnPos.x = transform.position.x + 16.f;
            spawnPos.y = midPoint.y;
        }
        if (movement.lastDirection.x > 0) 
        {
            sprite.srcRect.y = sprite.srcRect.h * 9; // right
            spawnPos.x = transform.position.x + 100.f;
            spawnPos.y = midPoint.y;
        }
        if (movement.lastDirection.y < 0) 
        {
            sprite.srcRect.y = sprite.srcRect.h * 11; // up
            spawnPos.x = midPoint.x;
            spawnPos.y = transform.position.y - 10.f;
        }
        if (movement.lastDirection.y > 0) 
        {
            sprite.srcRect.y = sprite.srcRect.h * 8; // down
            spawnPos.x = midPoint.x;
            spawnPos.y = transform.position.y + 90.f;
        }

        EntityFactory::CreateWeapon(WeaponType::BASIC, spawnPos, movement.lastDirection);

        //send an event
        EventManager::GetInstance().Notify<Entity>(EventType::OnBeginAnim, e);
    }
}

void AttackSpawningSystem::Update(float dt)
{
    
}