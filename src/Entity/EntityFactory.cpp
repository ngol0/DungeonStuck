#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(Registry& registry)
    {
        Entity e = registry.CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f), 20.f);
        e.AddComponent<MovementComponent>(2.f);

        return e;
    }
}