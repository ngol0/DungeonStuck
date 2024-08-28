#include "CameraMovementSystem.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"

#include "../Game/Scene.h"

CameraMovementSystem::CameraMovementSystem()
{
    RequireComponent<CameraFollowComponent>();
    RequireComponent<TransformComponent>();
}

void CameraMovementSystem::Update(float dt)
{
    auto entities = GetSystemEntities();
    for (auto entity : entities)
    {
        auto &transform = entity.GetComponent<TransformComponent>();

        if (transform.position.x + (Scene::camera.w / 2) < 640*2)
        {
            Scene::camera.x = transform.position.x - (800 / 2);
        }
        if (transform.position.y + (Scene::camera.h / 2) < 480*2)
        {
            Scene::camera.y = transform.position.y - (600 / 2);
        }

        Scene::camera.x = Scene::camera.x < 0 ? 0 : Scene::camera.x;
        Scene::camera.y = Scene::camera.y < 0 ? 0 : Scene::camera.y;
        Scene::camera.x = Scene::camera.x > Scene::camera.w ? Scene::camera.w : Scene::camera.x;
        Scene::camera.y = Scene::camera.y > Scene::camera.h ? Scene::camera.h : Scene::camera.y;
    }
}