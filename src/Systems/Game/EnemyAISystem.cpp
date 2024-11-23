#include "EnemyAISystem.h"

#include "../../Components/TransformComponent.h"
#include "../../Components/EnemyComponent.h"
#include "../../Components/MovementComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/AnimationComponent.h"
#include "../../Components/SpriteComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include "../../Game/AStarPathfinding.h"

EnemyAISystem::EnemyAISystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<EnemyComponent>();
    RequireComponent<MovementComponent>();
}

void EnemyAISystem::Init()
{
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnCollisionEnter, this, &EnemyAISystem::OnHitWall);
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnCollisionExit, this, &EnemyAISystem::OnAwayFromWall);

    EventManager::GetInstance().Register<Entity>(EventType::OnEntityDestroy, this, &EnemyAISystem::OnEnemyDieAnim);
    EventManager::GetInstance().Register<Entity>(EventType::OnDoneAnim, this, &EnemyAISystem::OnEnemyDestroy);
}

void EnemyAISystem::Update(float dt)
{
    //move back and forth
    for (auto &e : GetSystemEntities())
    {
        auto& movement = e.GetComponent<MovementComponent>();
        auto& transform = e.GetComponent<TransformComponent>();
        auto& enem = e.GetComponent<EnemyComponent>();

        // if slime - move back and forth
        if (enem.enemType == EnemyType::SLIME)
        {
            transform.position += (movement.moveDirection * movement.speed) * dt;

            if (transform.position.x < 0.f)
            {
                transform.position.x = 0.f;
                movement.moveDirection *= -1;
            }
            if (transform.position.x > 640.f)
            {
                transform.position.x = 640.f;
                movement.moveDirection *= -1;
            }
        }
        else if (enem.enemType == EnemyType::ZOMBIE)
        {
            // if advanced - move towards player
            // check distance to player
            
        }
    }
}

void EnemyAISystem::OnEnemyDieAnim(Entity& victim)
{
    if (victim.HasComponent<EnemyComponent>())
    {
        auto& anim = victim.GetComponent<AnimationComponent>();
        auto& sprite = victim.GetComponent<SpriteComponent>();
        auto& movement = victim.GetComponent<MovementComponent>();

        movement.speed = 0.f;

        anim.isLooping = false;
        anim.endOfSprite = false;
        anim.currentFrame = 0;
        anim.frameSpeed = 5;

        sprite.srcRect.y = sprite.srcRect.h * 0; // die
    }
}

void EnemyAISystem::OnEnemyDestroy(Entity& victim)
{
    if (victim.HasComponent<EnemyComponent>())
        victim.Destroy();
}

void EnemyAISystem::OnAwayFromWall(CollisionEventData& data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    int enemyId = -1;

    if (collider1.tag == Tag::ENEMY && collider2.tag == Tag::BLOCK)
    {
        enemyId = data.collisionPair.first;
    }
    else if (collider2.tag == Tag::ENEMY && collider1.tag == Tag::BLOCK)
    {
        enemyId = data.collisionPair.second;
    }
    if (enemyId == -1) return;

    //spdlog::info("Enemy collides with block!");

    Entity enemy(enemyId);

    auto& movement = enemy.GetComponent<MovementComponent>();
    movement.moveDirection *= -1;
    movement.speed = 80.f;
}

void EnemyAISystem::OnHitWall(CollisionEventData& data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    int enemyId = -1;
    int boxId = -1;

    if (collider1.tag == Tag::ENEMY && collider2.tag == Tag::BLOCK)
    {
        enemyId = data.collisionPair.first;
        boxId = data.collisionPair.second;
    }
    else if (collider2.tag == Tag::ENEMY && collider1.tag == Tag::BLOCK)
    {
        enemyId = data.collisionPair.second;
        boxId = data.collisionPair.first;
    }

    if (enemyId == -1 || boxId == -1) return;

    Entity enemy(enemyId);
    Entity block(boxId);

    auto &transform = enemy.GetComponent<TransformComponent>();
    auto &enemyBox = enemy.GetComponent<BoxColliderComponent>();
    auto& movement = enemy.GetComponent<MovementComponent>();

    auto &blockBox = block.GetComponent<BoxColliderComponent>();

    // A hack to check which direction is the overlap coming from
    // As the enemy is always bigger than the block, when overlap horizontally, width < height
    if (data.overlap.w < data.overlap.h)
    {
        // Resolve collision horizontally
        if (enemyBox.rect.x < blockBox.rect.x)
        {
            // Moving rect is on the left
            transform.position.x -= data.overlap.w; // Move left to prevent overlap
        }
        else
        {
            // Moving rect is on the right
            transform.position.x += data.overlap.w; // Move right to prevent overlap
        }
    }
    else
    {
        // Resolve collision vertically
        if (enemyBox.rect.y < blockBox.rect.y)
        {
            // Moving rect is up
            transform.position.y -= data.overlap.h;
        }
        else
        {
            // Moving rect is down
            transform.position.y += data.overlap.h;
        }
    }
    movement.speed = 0.f;
}