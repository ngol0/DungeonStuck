#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/PlayerInputComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos, glm::vec2 scale, float rot)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, scale, rot);

        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::CHOPPER);
        e.AddComponent<BoxColliderComponent>(Tag::PLAYER, sprite.srcRect.w/2, sprite.srcRect.h/4);
        e.AddComponent<MovementComponent>();
        e.AddComponent<AnimationComponent>(2, 4, 10);
        e.AddComponent<HealthComponent>(100.f);
        e.AddComponent<PlayerInputComponent>();

        return e;
    }

    Entity CreateEnemy(glm::vec2 pos, float speed, float health, glm::vec2 scale, float rot)
    {
        Entity e = Registry::GetInstance().CreateEntity();
        e.AddComponent<TransformComponent>(pos, glm::vec2(1.f, 1.f), 0.f);

        auto& sprite = e.AddComponent<SpriteComponent>(SpriteId::TANK);
        e.AddComponent<BoxColliderComponent>(Tag::ENEMY, sprite.srcRect.w - 5, sprite.srcRect.h, glm::vec2(4.f, 0.f));
        e.AddComponent<MovementComponent>(speed);

        return e;
    }
}