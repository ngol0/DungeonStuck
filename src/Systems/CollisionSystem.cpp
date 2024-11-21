#include "CollisionSystem.h"

#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Events/EventManager.h"
#include "../Events/EventType.h"

CollisionSystem::CollisionSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

void CollisionSystem::Init()
{
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnEntityDestroy, this, &CollisionSystem::OnEntityDestroy);
}

void CollisionSystem::OnEntityDestroy(CollisionEventData& data)
{
    auto iter = m_collisionMap.find(data.collisionPair);
    if (iter != m_collisionMap.end())
    {
        spdlog::info("Reset collision between: " +
            std::to_string(data.collisionPair.first) + 
            " and " + std::to_string(data.collisionPair.second));
        iter->second = false;
    }
}

void CollisionSystem::Update(float dt)
{
    auto entities = GetSystemEntities();

    for (auto iter = entities.begin(); iter != entities.end(); iter++)
    {
        Entity first = *iter;
        auto &firstBox = first.GetComponent<BoxColliderComponent>();
        auto &firstTransform = first.GetComponent<TransformComponent>();

        for (auto iter2 = iter + 1; iter2 != entities.end(); iter2++)
        {
            Entity second = *iter2;
            auto &secondBox = second.GetComponent<BoxColliderComponent>();
            auto &secondTransform = second.GetComponent<TransformComponent>();

            if (firstBox.tag == secondBox.tag) 
            {
                //spdlog::info("Two colliders with same tag: " + firstBox.tag);
                continue;
            }

            firstBox.rect.x = firstTransform.position.x + firstBox.offset.x;
            firstBox.rect.y = firstTransform.position.y + firstBox.offset.y;
            secondBox.rect.x = secondTransform.position.x + secondBox.offset.x;
            secondBox.rect.y = secondTransform.position.y + secondBox.offset.y;

            SDL_Rect overlap;

            bool currentCollisionStatus = SDL_IntersectRect(&firstBox.rect, &secondBox.rect, &overlap);
    
            auto key = std::make_pair(first.GetId(), second.GetId());
            CollisionEventData data(key, overlap, dt);

            if (currentCollisionStatus != m_collisionMap[key])
			{
				// If two are collided -> on collision enter
				if (currentCollisionStatus)
				{
					//spdlog::info("On Collision Enter");

                    // Update the collision map with the current status & emit event
				    m_collisionMap[key] = currentCollisionStatus;
                    EventManager::GetInstance().Notify(EventType::OnCollisionEnter, data);
					
				}
				// If two are not collided -> on collision exit
				else
				{
					//spdlog::info("On Collision Exit");

                    // Update the collision map with the current status & emit event
				    m_collisionMap[key] = currentCollisionStatus;
                    EventManager::GetInstance().Notify(EventType::OnCollisionExit, data);
				}
			}
			// If status hasn't changed and they were collided on last frame, on collision stay 
			else if (currentCollisionStatus == m_collisionMap[key] && currentCollisionStatus)
			{
                //spdlog::info("On Collision Stay");
				EventManager::GetInstance().Notify(EventType::OnCollisionStay, data);
			}
        }
    }
}