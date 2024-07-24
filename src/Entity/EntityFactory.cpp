#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

namespace EntityFactory
{
    Entity CreatePlayer(Registry& registry)
    {
        Entity e = registry.CreateEntity();
        e.AddComponent<TransformComponent>(glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f), 20.f);
        //e.AddComponent<BoxColliderComponent>();

        return e;
    }
}