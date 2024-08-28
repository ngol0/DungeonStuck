#include "PlayerMovementSystem.h"

#include "../../Components/MovementComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/PlayerInputComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/BoxColliderComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include <SDL2/SDL.h>

PlayerMovementSystem::PlayerMovementSystem()
{
    RequireComponent<PlayerInputComponent>();
    RequireComponent<TransformComponent>();
    RequireComponent<MovementComponent>();
    RequireComponent<SpriteComponent>();
}

void PlayerMovementSystem::Init()
{
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &PlayerMovementSystem::OnStartHit);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionStay, this, &PlayerMovementSystem::OnKeepHitting);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionExit, this, &PlayerMovementSystem::OnDoneHitting);
}

void PlayerMovementSystem::Move(glm::vec3 &value, float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &movement = e.GetComponent<MovementComponent>();
        auto &sprite = e.GetComponent<SpriteComponent>();
        auto &transform = e.GetComponent<TransformComponent>();

        // Movement

        //testing - has some weird bugs with speed and direction// todo: investigate later
        // glm::vec2 dir = glm::vec2{value.x, value.y};
        // movement.moveDirection += dir;
        // if (glm::length(movement.moveDirection) != 0) movement.moveDirection = glm::normalize(movement.moveDirection);
        // value.z = (movement.moveDirection.x < 0) ? 1.f : 3.f;
        glm::vec2 moveDir = glm::vec2{value.x, value.y};
        if (value.x != 0) movement.moveDirection.x = value.x;

        value.z = movement.moveDirection.x < 0 ? 1 : 3;
        sprite.srcRect.y = sprite.srcRect.h * value.z;

        transform.position += (moveDir * movement.speed) * dt * m_moveVariable;
    }
}

void PlayerMovementSystem::Update(float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &sprite = e.GetComponent<SpriteComponent>();
        auto &movement = e.GetComponent<MovementComponent>();

        sprite.srcRect.y = (movement.moveDirection.x < 0) ? 0 : sprite.srcRect.h * 2;
    }
}

void PlayerMovementSystem::OnStartHit(CollisionData &data)
{
    m_forceCount++;
    m_force = m_initialForce/m_forceCount;
}

void PlayerMovementSystem::OnKeepHitting(CollisionData &data)
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

    Entity player(playerId);
    Entity block(boxId);

    auto &transform = player.GetComponent<TransformComponent>();
    auto &playerBox = player.GetComponent<BoxColliderComponent>();
    //auto &movement = player.GetComponent<MovementComponent>();

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

void PlayerMovementSystem::OnDoneHitting(CollisionData &data)
{
    m_moveVariable = 1.f;
    m_forceCount--;
    m_force = m_initialForce/m_forceCount;
}