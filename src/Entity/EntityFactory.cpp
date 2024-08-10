#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"

#include "../Global/AssetManager.h"

namespace EntityFactory
{
    Entity CreateTank()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(300.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(-50.f);
        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::TANK);
        e.AddComponent<BoxColliderComponent>(Tag::ENEMY, sprite.srcRect.w - 5, sprite.srcRect.h, glm::vec2(4.f, 0.f));

        return e;
    }

    //for testing
    Entity CreateTank2()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(500.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(-90.f);
        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::TANK);
        e.AddComponent<BoxColliderComponent>(Tag::ENEMY, sprite.srcRect.w - 5, sprite.srcRect.h, glm::vec2(4.f, 0.f));

        return e;
    }

    Entity CreateChopper()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(50.f);
        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::CHOPPER);
        e.AddComponent<AnimationComponent>(2, 10);
        e.AddComponent<BoxColliderComponent>(Tag::PLAYER, sprite.srcRect.w/2, sprite.srcRect.h);
        e.AddComponent<HealthComponent>(100.f);

        return e;
    }
}