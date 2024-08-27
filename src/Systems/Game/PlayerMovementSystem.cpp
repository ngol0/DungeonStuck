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
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &PlayerMovementSystem::OnHitWall);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionExit, this, &PlayerMovementSystem::OnAwayFromWall);
}

void PlayerMovementSystem::Move(glm::vec3 &value, float dt)
{
    for (auto &e : GetSystemEntities())
    {
        auto &movement = e.GetComponent<MovementComponent>();
        auto &sprite = e.GetComponent<SpriteComponent>();
        auto &transform = e.GetComponent<TransformComponent>();

        // Movement
        // glm::vec2 dir = glm::vec2{value.x, value.y};
        // movement.moveDirection += dir;

        // if (glm::length(movement.moveDirection) != 0) movement.moveDirection = glm::normalize(movement.moveDirection);

        // value.z = (movement.moveDirection.x < 0) ? 1.f : 3.f;
        sprite.srcRect.y = sprite.srcRect.h * value.z;

        movement.moveDirection.x = value.x;
        movement.moveDirection.y = value.y;

        transform.position += (movement.moveDirection * movement.speed) * dt * variable;
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

void PlayerMovementSystem::OnHitWall(CollisionData &data)
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
    auto &movement = player.GetComponent<MovementComponent>();

    auto &blockBox = block.GetComponent<BoxColliderComponent>();

    // Calculate the overlap direction
    // int overlapX = std::min(playerBox.rect.x + playerBox.rect.w, blockBox.rect.x + blockBox.rect.w) 
    //     - std::max(playerBox.rect.x, blockBox.rect.x);
    // int overlapY = std::min(playerBox.rect.y + playerBox.rect.h, blockBox.rect.y + blockBox.rect.h) 
    //     - std::max(playerBox.rect.y, blockBox.rect.y);

    glm::vec2 dir;
    int overlapAmt;

    if (data.overlap.w < data.overlap.h)
    {
        // Resolve collision horizontally
        if (playerBox.rect.x < blockBox.rect.x)
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
        // Resolve collision horizontally
        if (playerBox.rect.y < blockBox.rect.y)
        {
            // Moving rect is on the left
            transform.position.y -= data.overlap.h; // Move left to prevent overlap
        }
        else
        {
            // Moving rect is on the right
            transform.position.y += data.overlap.h; // Move right to prevent overlap
        }
    }
    variable = 0.f;
}

void PlayerMovementSystem::OnAwayFromWall(CollisionData &data)
{
    variable = 1.f;
}