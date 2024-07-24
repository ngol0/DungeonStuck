#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

namespace EntityFactory
{
    void CreatePlayer(Registry& registry)
    {
        auto e = registry.CreateEntity();
        registry.AddComponent<TransformComponent>(e, glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f), 20.f);
        registry.AddComponent<BoxColliderComponent>(e);
    }
}