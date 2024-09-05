#include "PlayerActionSystem.h"

#include "../../Components/MovementComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/AnimationComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include <SDL2/SDL.h>

PlayerActionSystem::PlayerActionSystem()
{
    RequireComponent<PlayerInputComponent>();
    RequireComponent<TransformComponent>();
    RequireComponent<MovementComponent>();
    RequireComponent<SpriteComponent>();
    RequireComponent<AnimationComponent>();
}

void PlayerActionSystem::Init()
{
    //for collision with wall
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &PlayerActionSystem::OnStartHitWall);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionStay, this, &PlayerActionSystem::OnKeepHittingWall);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionExit, this, &PlayerActionSystem::OnDoneHittingWall);

    //for attack anim and other anims
    EventManager::GetInstance().Register<Entity>(EventType::OnBeginAnim, this, &PlayerActionSystem::OnStartAttack);
    EventManager::GetInstance().Register<Entity>(EventType::OnDoneAnim, this, &PlayerActionSystem::OnEndAttack);

    //for player die
    EventManager::GetInstance().Register<Entity>(EventType::OnEntityDestroy, this, &PlayerActionSystem::OnPlayerDie);
}

void PlayerActionSystem::Move(glm::vec3 &value, float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &movement = e.GetComponent<MovementComponent>();
        auto &sprite = e.GetComponent<SpriteComponent>();
        auto &transform = e.GetComponent<TransformComponent>();
        auto &anim = e.GetComponent<AnimationComponent>();

        // Movement
        glm::vec2 dir = glm::vec2{value.x, value.y};
        movement.moveDirection += dir;
        
        if (glm::length(movement.moveDirection) != 0)
        {
            movement.moveDirection = glm::normalize(movement.moveDirection);
            movement.lastDirection = movement.moveDirection;
        } 

        //log to test
        //spdlog::info("Move x: " + std::to_string(movement.moveDirection.x));
        //spdlog::info("Move y: " + std::to_string(movement.moveDirection.y));

        //old way: not correct but leave here in case of useful to test around
        //glm::vec2 moveDir = glm::vec2{value.x, value.y};
        //if (value.x != 0) movement.moveDirection.x = value.x;
        //movement.moveDirection = moveDir;
        if (m_isAttacking) return;
        anim.isLooping = true;
        sprite.srcRect.y = sprite.srcRect.h * value.z;

        //
        transform.position += (movement.moveDirection * movement.speed) * dt * m_moveVariable;
    }
}

void PlayerActionSystem::Update(float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &movement = e.GetComponent<MovementComponent>();
        auto &sprite = e.GetComponent<SpriteComponent>();
        auto &anim = e.GetComponent<AnimationComponent>();
        movement.moveDirection = glm::vec2(0, 0);

        //
        if (m_isAttacking) return;

        anim.isLooping = true;

        if (movement.lastDirection.x < 0) sprite.srcRect.y = sprite.srcRect.h * 0; // left
        if (movement.lastDirection.x > 0) sprite.srcRect.y = sprite.srcRect.h * 2; // right
        if (movement.lastDirection.y < 0) sprite.srcRect.y = sprite.srcRect.h * 3; // up
        if (movement.lastDirection.y > 0) sprite.srcRect.y = sprite.srcRect.h * 1; // down
    }
}

void PlayerActionSystem::OnStartAttack(Entity& attacker)
{
    if (attacker.HasComponent<PlayerInputComponent>())
    {
        m_isAttacking = true;
    }
}

void PlayerActionSystem::OnEndAttack(Entity& attacker)
{
    if (attacker.HasComponent<PlayerInputComponent>())
    {
        m_isAttacking = false;
    }
}

void PlayerActionSystem::OnPlayerDie(Entity& victim)
{
    if (victim.HasComponent<PlayerInputComponent>())
    {
       spdlog::info("Player die");
    }
}

void PlayerActionSystem::OnStartHitWall(CollisionData &data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    if (collider1.tag != Tag::PLAYER && collider2.tag != Tag::PLAYER) return;
    if (collider1.tag == Tag::PLAYER && collider2.tag != Tag::BLOCK) return;
    if (collider2.tag == Tag::PLAYER && collider1.tag != Tag::BLOCK) return;

    m_forceCount++;
    m_force = m_initialForce/m_forceCount;
}

void PlayerActionSystem::OnKeepHittingWall(CollisionData &data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    int playerId = -1;
    int boxId = -1;
    if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::BLOCK)
    {
        playerId = data.collisionPair.first;
        boxId = data.collisionPair.second;
    }
    else if (collider2.tag == Tag::PLAYER && collider1.tag == Tag::BLOCK)
    {
        playerId = data.collisionPair.second;
        boxId = data.collisionPair.first;
    }

    if (playerId == -1 || boxId == -1) return;

    Entity player(playerId);
    Entity block(boxId);

    auto &transform = player.GetComponent<TransformComponent>();
    auto &playerBox = player.GetComponent<BoxColliderComponent>();

    auto &blockBox = block.GetComponent<BoxColliderComponent>();

    // A hack to check which direction is the overlap coming from
    // As the player is always bigger than the block, when overlap horizontally, width < height
    if (data.overlap.w < data.overlap.h)
    {
        // Resolve collision horizontally
        if (playerBox.rect.x < blockBox.rect.x)
        {
            // Moving rect is on the left
            transform.position.x -= data.overlap.w * data.dt * m_force; // Move left to prevent overlap
        }
        else
        {
            // Moving rect is on the right
            transform.position.x += data.overlap.w * data.dt * m_force; // Move right to prevent overlap
        }
    }
    else
    {
        // Resolve collision vertically
        if (playerBox.rect.y < blockBox.rect.y)
        {
            // Moving rect is up
            transform.position.y -= data.overlap.h * data.dt * m_force;
        }
        else
        {
            // Moving rect is down
            transform.position.y += data.overlap.h * data.dt * m_force;
        }
    }
    m_moveVariable = 0.f;
}

void PlayerActionSystem::OnDoneHittingWall(CollisionData &data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    if (collider1.tag != Tag::PLAYER && collider2.tag != Tag::PLAYER) return;
    if (collider1.tag == Tag::PLAYER && collider2.tag != Tag::BLOCK) return;
    if (collider2.tag == Tag::PLAYER && collider1.tag != Tag::BLOCK) return;

    m_moveVariable = 1.f;
    m_forceCount--;
    m_force = m_initialForce/m_forceCount;
}