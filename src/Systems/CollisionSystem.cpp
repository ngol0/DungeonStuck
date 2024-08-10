#include "CollisionSystem.h"

#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../ECS/ECS.h"
#include "../Events/EventManager.h"
#include "../Events/EventType.h"

#include <spdlog/spdlog.h>

CollisionSystem::CollisionSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
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

            if (firstBox.tag == secondBox.tag) continue;

            SDL_Rect firstRect = {
                static_cast<int>(firstTransform.position.x + firstBox.offset.x),
                static_cast<int>(firstTransform.position.y + firstBox.offset.y),
                static_cast<int>(firstBox.width),
                static_cast<int>(firstBox.height)};

            SDL_Rect secondRect = {
                static_cast<int>(secondTransform.position.x + secondBox.offset.x),
                static_cast<int>(secondTransform.position.y + secondBox.offset.y),
                static_cast<int>(secondBox.width),
                static_cast<int>(secondBox.height)};

            bool currentCollisionStatus = SDL_HasIntersection(&firstRect, &secondRect);
    
            auto key = std::make_pair(first.GetId(), second.GetId());
            CollisionData data(key);

            if (currentCollisionStatus != m_collisionMap[key])
			{
				// If two are collided -> on collision enter
				if (currentCollisionStatus)
				{
					spdlog::info("On Collision Enter");

                    //todo: when destroy an entity > that entity is removed from the system entities array
                    //but it still exists in the map of current status
                    //when that entity id is reused
                    //might cause problems?
                    //>>solution: when collide > call damage system >> when health hits 0 >> call another event
                    //collision system listens to that event and update the map?

                    //emit an event
                    EventManager::GetInstance().Notify(EventType::OnCollisionEnter, data);
					
				}
				// If two are not collided -> on collision exit
				else
				{
					spdlog::info("On Collision Exit");
                    EventManager::GetInstance().Notify(EventType::OnCollisionExit, data);
				}

				// Update the collision map with the current status
				m_collisionMap[key] = currentCollisionStatus;
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