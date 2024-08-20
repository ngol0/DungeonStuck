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
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionExit, this, &PlayerMovementSystem::OnWalkablePath);
}

void PlayerMovementSystem::Move(glm::vec3& value, float dt)
{
    for (auto& e : GetSystemEntities())
    {
        auto& movement = e.GetComponent<MovementComponent>();
        auto& sprite = e.GetComponent<SpriteComponent>();
        auto& transform = e.GetComponent<TransformComponent>();
        
        //
        int x = value.x;
        int y = value.y;

        if (movement.isBlockRight) x = SDL_clamp(value.x, -1.f, 0.f);
        else if (movement.isBlockLeft) x = SDL_clamp(value.x, 0.f, 1.f);

        if (movement.isBlockDown) y = SDL_clamp(value.y, -1.f, 0.f);
        else if (movement.isBlockUp) y = SDL_clamp(value.y, 0.f, 1.f);

        movement.moveDirection = glm::vec2(x, y);
        sprite.srcRect.y = sprite.srcRect.h * value.z;

        transform.position += movement.moveDirection * movement.speed * dt;
    }
}

void PlayerMovementSystem::OnHitWall(CollisionData& data)
{
    Entity player = GetPlayer(data);
    if (player.GetId() == -1) return;
    auto& movement = player.GetComponent<MovementComponent>();
    
    // Check horizontal collision
    if (movement.moveDirection.x > 0) 
    {
        // Moving right, collision on the right side
        movement.isBlockRight = true;
    } 
    else if (movement.moveDirection.x < 0) 
    {
        // Moving left, collision on the left side
        movement.isBlockLeft = true;
    }

    // Check vertical collision
    if (movement.moveDirection.y > 0) 
    {
        // Moving down, collision from below
        movement.isBlockDown = true;
    } 
    else if (movement.moveDirection.y < 0) 
    {
        // Moving up, collision from above
        movement.isBlockUp = true;
    }
}

void PlayerMovementSystem::OnWalkablePath(CollisionData& data)
{
    Entity player = GetPlayer(data);
    if (player.GetId() == -1) return;
    auto& movement = player.GetComponent<MovementComponent>();
    auto& transform = player.GetComponent<TransformComponent>();

    movement.isBlockDown = false;
    movement.isBlockRight = false;
    movement.isBlockLeft = false;
    movement.isBlockUp = false;
}

Entity PlayerMovementSystem::GetPlayer(CollisionData& data)
{
    auto& collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto& collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    int playerId = -1;
    if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::ENEMY_BULLET)
    {
        playerId = data.collisionPair.first;
    }
    else if (collider2.tag == Tag::PLAYER && collider1.tag == Tag::ENEMY_BULLET)
    {
        playerId = data.collisionPair.second;
    }
    Entity player(playerId);
    return player;
}