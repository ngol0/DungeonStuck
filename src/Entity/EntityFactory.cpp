#include "EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"

#include "../Global/AssetManager.h"

namespace EntityFactory
{
    Entity CreatePlayer(Registry& registry)
    {
        Entity e = registry.CreateEntity();
        auto& transform = e.AddComponent<TransformComponent>(glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f), 0.f);
        e.AddComponent<MovementComponent>(100.f);
        e.AddComponent<SpriteComponent>(SpriteId::PLAYER_TANK, 50, 50); //todo: not hard code the size

        return e;
    }
}