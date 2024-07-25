#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(Registry& registry)
    {
        Entity e = registry.CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(1.f, 1.f), glm::vec2(10.f, 10.f), 0.f);
        e.AddComponent<MovementComponent>(100.f);
        e.AddComponent<SpriteComponent>();

        return e;
    }
}