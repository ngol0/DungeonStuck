#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

#include "../Global/AssetManager.h"

namespace EntityFactory
{
    Entity CreatePlayer()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(1.f, 100.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(100.f);
        e.AddComponent<SpriteComponent>(SpriteId::TANK);

        return e;
    }

    Entity CreateChopper()
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(100.f);
        e.AddComponent<SpriteComponent>(SpriteId::CHOPPER);
        e.AddComponent<AnimationComponent>(2, 10);

        return e;
    }
}