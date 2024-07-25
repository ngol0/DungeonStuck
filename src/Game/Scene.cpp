#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include <spdlog/spdlog.h>

void Scene::Init()
{
    //Create system
    registry.AddSystem<MovementSystem>();
    registry.AddSystem<RenderSystem>();

    //Create entity
    auto player = EntityFactory::CreatePlayer(registry); //when create entity > entity added to m_added
}

void Scene::Update(float deltaTime)
{
    registry.Update(deltaTime); //entities in m_added added to relevant system
}

void Scene::Render(SDL_Renderer* renderer)
{
    registry.Render(renderer);
}

void Scene::Shutdown()
{

}
