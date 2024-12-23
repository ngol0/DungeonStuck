#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/HealthUIComponent.h"
#include "../Components/PlayerInputComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/WeaponComponent.h"
#include "../Components/EnemyComponent.h"
#include "../Components/ItemComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/InventoryUIComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/PathNodeComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos)
    {
        glm::vec2 scale = glm::vec2{2.7f};
        float rot = 0.f;

        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, scale, rot);

        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::PLAYER, 1);
        e.AddComponent<BoxColliderComponent>
        (
            Tag::PLAYER, 
            sprite.srcRect.w/6 * scale.x - 104.f, 
            sprite.srcRect.h/13 * scale.y - 40.f, 
            glm::vec2(54.f, 16.f)
        );
        e.AddComponent<MovementComponent>(250.f);
        e.AddComponent<AnimationComponent>(6, 14, 7);
        e.AddComponent<HealthComponent>(300);
        e.AddComponent<PlayerInputComponent>();
        e.AddComponent<CameraFollowComponent>();
        e.AddComponent<InventoryComponent>();

        return e;
    }

    Entity CreateWeapon(WeaponType type, glm::vec2 spawnPos, glm::vec2 moveDir)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(spawnPos, glm::vec2{1.5f}, 0.f);

        if (type == WeaponType::BASIC)
        {
            //e.AddComponent<SpriteComponent>(SpriteId::BASIC_WEAPON);
            e.AddComponent<WeaponComponent>(20.f, 0.3f);
            e.AddComponent<MovementComponent>(300.f, moveDir);
            e.AddComponent<BoxColliderComponent>(Tag::PLAYER_BULLET, 32.f, 16.f, glm::vec2(0.f, 0.f));
        }

        return e;
    }

    Entity CreateEnemy(glm::vec2 pos, glm::vec2 moveDir, EnemyType type)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<EnemyComponent>();

        if (type == EnemyType::SLIME)
        {
            glm::vec2 scale = glm::vec2{2.f};

            e.AddComponent<TransformComponent>(pos, scale, 0.f);
            auto& anim = e.AddComponent<AnimationComponent>(7, 5, 6);
            auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::SLIME);
            sprite.srcRect.y = 1 * 32; //todo : move this to ai systme later
            anim.isLooping = true;
            e.AddComponent<BoxColliderComponent>
            (
                Tag::ENEMY, 
                sprite.srcRect.w/7 * scale.x - 26.f, 
                sprite.srcRect.h/5 * scale.y - 30.f, 
                glm::vec2(16.f, 16.f)
            );
            auto& movement = e.AddComponent<MovementComponent>(80.f);
            movement.moveDirection = moveDir;
            e.AddComponent<HealthComponent>(100.f);
            e.AddComponent<EnemyComponent>(type);
        }
        else if (type == EnemyType::ZOMBIE)
        {
            glm::vec2 scale = glm::vec2{2.f};

            e.AddComponent<TransformComponent>(pos, scale, 0.f);
            auto& anim = e.AddComponent<AnimationComponent>(4, 4, 8);
            auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::ZOMBIE);
            anim.isLooping = true;
            e.AddComponent<BoxColliderComponent>
            (
                Tag::ENEMY, 
                sprite.srcRect.w/7 * scale.x - 26.f, 
                sprite.srcRect.h/5 * scale.y - 30.f, 
                glm::vec2(16.f, 16.f)
            );
            //auto& movement = e.AddComponent<MovementComponent>(80.f);
            //movement.moveDirection = moveDir;
            e.AddComponent<HealthComponent>(100.f);
            e.AddComponent<EnemyComponent>(type);
        }

        return e;
    }

    Entity CreateItem(glm::vec2 pos, ItemType type)
    {
        float scale = 2.f;
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, glm::vec2{scale}, 0.f);
        e.AddComponent<ItemComponent>(type);
        auto &sprite = e.AddComponent<SpriteComponent>(SpriteId::CHEST);
        e.AddComponent<BoxColliderComponent>
        (
            Tag::ITEM,
            sprite.srcRect.w * scale,
            sprite.srcRect.h * scale,
            glm::vec2{0.f}
        );

        return e;
    }

    //---------------------------------------------Tile------------------------------------------------------------------------
    Entity CreateTile(glm::vec2 size, glm::vec2 srcRect, glm::vec2 pos, float rot, glm::vec2 boxSize)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        float scale = 2.f;

        e.AddComponent<SpriteComponent>(
            SpriteId::MAP, -1,
            static_cast<int>(srcRect.x), static_cast<int>(srcRect.y),
            static_cast<int>(size.x), static_cast<int>(size.y));

        float tilePosX = pos.x * scale;
        float tilePosY = pos.y * scale;
        GridPosition gridPosition = Utils::TileToGridPos(glm::vec2(tilePosX, tilePosY));
        e.AddComponent<TransformComponent>(glm::vec2(tilePosX, tilePosY), glm::vec2{scale}, rot);
        auto& pathNode = e.AddComponent<PathNodeComponent>(gridPosition);

        //check to see if tile has box collider -- which means war and obstacles
        if (boxSize.x != 0)
        {
            e.AddComponent<BoxColliderComponent>(Tag::BLOCK, boxSize.x * scale, boxSize.y * scale, glm::vec2{0.f});
            pathNode.isWalkable = false;
        }
        //if not it means walkable path
        else
        {
            pathNode.isWalkable = true;
        }

        //SDL_Color black = { 0, 0, 0, 255 };
        //GridPosition gridPos = Utils::TileToGridPos(glm::vec2(tilePosX, tilePosY));
        // e.AddComponent<TextComponent>(
        //     glm::vec2(tilePosX, tilePosY), 
        //     "(" + std::to_string(gridPos.x) + ", " + std::to_string(gridPos.y) + ")", 
        //     SpriteId::OTHER_TEXT, black, true);

        return e;
    }

    //---------------------------------------------Game UI---------------------------------------------------------------------
    Entity CreateInventorySlotUI(glm::vec2 pos)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<UIComponent>(SpriteId::UI_SLOT_INVENTORY);
        e.AddComponent<TransformComponent>(pos, glm::vec2{1.5f}, 0.f);

        return e;
    }

    Entity CreateInventoryItemUI(glm::vec2 pos, ItemType type, int idx)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, glm::vec2{2.f}, 0.f);
        e.AddComponent<InventoryUIComponent>(idx);
        SDL_Color black = { 0, 0, 0, 255 };
        e.AddComponent<TextComponent>(glm::vec2{pos.x - 5.f, pos.y}, "", SpriteId::STANDARD_TEXT, black, true);

        switch (type)
        {
        case ItemType::HEALTH_PORTION:
            e.AddComponent<UIComponent>(SpriteId::HEALTH_ITEM);
            break;

        case ItemType::STRENTH_PORTION:
            e.AddComponent<UIComponent>(SpriteId::STRENGTH_ITEM);
            break;

        default:
            e.AddComponent<UIComponent>(SpriteId::NONE);
            break;
        }

        return e;
    }

    Entity CreateHealthUI(glm::vec2 pos)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, glm::vec2{1.f}, 0.f);
        e.AddComponent<UIComponent>(SpriteId::UI_HEALTH);
        e.AddComponent<HealthUIComponent>();

        SDL_Color black = { 0, 0, 0, 255 };
        e.AddComponent<TextComponent>(glm::vec2{pos.x + 40.f, pos.y}, "3/3", SpriteId::OTHER_TEXT, black, true);

        return e;
    }
}