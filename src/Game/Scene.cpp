#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include <spdlog/spdlog.h>

void Scene::Init()
{
    auto player = EntityFactory::CreatePlayer(registry);
    auto trform = player.GetComponent<TransformComponent>();
    BoxColliderComponent* box = player.GetComponent<BoxColliderComponent>();

    if (box == nullptr)
    {
        spdlog::info("Box is null");
    }
    spdlog::info("Transform: " + std::to_string(trform->rotation));
    trform->rotation = 50.f;
    spdlog::info("Transform: " + std::to_string(trform->rotation));
}

void Scene::Update(float deltaTime)
{

}

void Scene::Render()
{

}

void Scene::Shutdown()
{

}
