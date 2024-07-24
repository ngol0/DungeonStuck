#include "Scene.h"
#include "../Entity/EntityFactory.h"

void Scene::Init()
{
    auto player = EntityFactory::CreatePlayer(registry);
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
