#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../Global/AssetManager.h"

namespace EntityFactory
{
    Entity CreateTank()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(300.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(-50.f);
        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::TANK);
        e.AddComponent<BoxColliderComponent>("tank", sprite.srcRect.w, sprite.srcRect.h);

        return e;
    }

    Entity CreateChopper()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(50.f);
        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::CHOPPER);
        e.AddComponent<AnimationComponent>(2, 10);
        e.AddComponent<BoxColliderComponent>("chopper", sprite.srcRect.w, sprite.srcRect.h);

        return e;
    }
}