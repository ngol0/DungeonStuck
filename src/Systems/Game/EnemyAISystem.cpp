#include "EnemyAISystem.h"

#include "../../Components/TransformComponent.h"
#include "../../Components/EnemyComponent.h"
#include "../../Components/MovementComponent.h"

EnemyAISystem::EnemyAISystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<EnemyComponent>();
    RequireComponent<MovementComponent>();
}