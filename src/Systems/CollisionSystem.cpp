#include "CollisionSystem.h"

#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../ECS/ECS.h"

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
                static_cast<int>(firstTransform.position.x),
                static_cast<int>(firstTransform.position.y),
                static_cast<int>(firstBox.width),
                static_cast<int>(firstBox.height)};

            SDL_Rect secondRect = {
                static_cast<int>(secondTransform.position.x),
                static_cast<int>(secondTransform.position.y),
                static_cast<int>(secondBox.width),
                static_cast<int>(secondBox.height)};

            bool currentCollisionStatus = SDL_HasIntersection(&firstRect, &secondRect);

            auto key = std::make_pair(first, second);

            if (currentCollisionStatus != collision_map[key])
			{
				// If two are collided -> on collision enter
				if (currentCollisionStatus)
				{
					spdlog::info(
                        "On Collision Enter between: " + std::to_string(first.GetId()) + " and " + std::to_string(second.GetId()));
					//colliders[i]->collision_enter.Notify(*colliders[j]);
					//colliders[j]->collision_enter.Notify(*colliders[i]);

					//colliders[i]->collisions_enter.Notify(*colliders[i], *colliders[j]);
					//colliders[j]->collisions_enter.Notify(*colliders[j], *colliders[i]);
				}
				// If two are not collided -> on collision exit
				else
				{
					spdlog::info("On Collision Exit");
					//colliders[i]->collision_exit.Notify(*colliders[j]);
					//colliders[j]->collision_exit.Notify(*colliders[i]);
				}

				// Update the collision map with the current status
				collision_map[key] = currentCollisionStatus;
			}
			// If status hasn't changed and they were collided on last frame, on collision stay 
			else if (currentCollisionStatus == collision_map[key] && currentCollisionStatus)
			{
                //spdlog::info("On Collision Stay");
				//colliders[i]->collision_stay.Notify(*colliders[j]);
				//colliders[j]->collision_stay.Notify(*colliders[i]);
			}
        }
    }
}