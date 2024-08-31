#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/PlayerInputComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/WeaponComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos)
    {
        glm::vec2 scale = glm::vec2{3.f};
        float rot = 0.f;

        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, scale, rot);

        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::PLAYER);
        e.AddComponent<BoxColliderComponent>(
                Tag::PLAYER, sprite.srcRect.w/6 * scale.x - 104.f, sprite.srcRect.h/13 * scale.y - 32.f, glm::vec2(54.f, 16.f));
        e.AddComponent<MovementComponent>(300.f);
        e.AddComponent<AnimationComponent>(6, 14, 5);
        e.AddComponent<HealthComponent>(100.f);
        e.AddComponent<PlayerInputComponent>();
        e.AddComponent<CameraFollowComponent>();

        return e;
    }

    Entity CreateWeapon(WeaponType type, glm::vec2 spawnPos, glm::vec2 moveDir)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(spawnPos, glm::vec2{1.5f}, 0.f);

        if (type == WeaponType::BASIC)
        {
            auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::BASIC_WEAPON);
            e.AddComponent<WeaponComponent>(20.f, 0.5f);
            e.AddComponent<MovementComponent>(400.f, moveDir);
        }

        return e;
    }

    //todo: implement real enemies
    Entity CreateEnemy(glm::vec2 pos, float speed, float health, glm::vec2 scale, float rot)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, glm::vec2(1.f, 1.f), 0.f);

        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::TANK);
        e.AddComponent<BoxColliderComponent>(Tag::ENEMY_BULLET, sprite.srcRect.w - 5, sprite.srcRect.h, glm::vec2(4.f, 0.f));
        e.AddComponent<MovementComponent>(speed);

        return e;
    }

    //---------------------------------------------Tile------------------------------------------------------------------------
    Entity CreateTile(glm::vec2 size, glm::vec2 srcRect, glm::vec2 pos, float rot, glm::vec2 boxSize)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        float scale = 2.f;

        e.AddComponent<SpriteComponent>(
            SpriteId::MAP, 
            static_cast<int>(srcRect.x), static_cast<int>(srcRect.y),
            static_cast<int>(size.x), static_cast<int>(size.y));

        e.AddComponent<TransformComponent>(glm::vec2(pos.x * scale, pos.y * scale), glm::vec2{scale}, rot);

        //check to see if tile has box collider
        if (boxSize.x != 0)
        {
            e.AddComponent<BoxColliderComponent>(Tag::BLOCK, boxSize.x * scale, boxSize.y * scale, glm::vec2{0.f});
        }

        return e;
    }
}