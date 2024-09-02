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

        glm::vec2 spawnPos = glm::vec2(transform.position.x + 20.f, transform.position.y + 32.f);
        EntityFactory::CreateWeapon(WeaponType::BASIC, spawnPos, movement.lastDirection);

        // change sprite
        auto &sprite = e.GetComponent<SpriteComponent>();
        anim.isLooping = false;
        anim.endOfSprite = false;

        anim.currentFrame = 0;
        if (movement.lastDirection.x < 0) sprite.srcRect.y = sprite.srcRect.h * 10; // left
        if (movement.lastDirection.x > 0) sprite.srcRect.y = sprite.srcRect.h * 9; // right
        if (movement.lastDirection.y < 0) sprite.srcRect.y = sprite.srcRect.h * 11; // up
        if (movement.lastDirection.y > 0) sprite.srcRect.y = sprite.srcRect.h * 8; // down

        //send an event
        EventManager::GetInstance().Notify<IData>(EventType::OnBeginAnim, IData());
    }
}

void AttackSpawningSystem::Update(float dt)
{
    
}