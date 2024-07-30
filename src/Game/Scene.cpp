#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

#include "../Global/AssetManager.h"

#include <spdlog/spdlog.h>

void Scene::Init(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::PLAYER_TANK, "./assets/images/tank-panther-right.png");

    //Create system
    m_registry.AddSystem<MovementSystem>();
    m_registry.AddSystem<RenderSystem>();

    //Create entity
    EntityFactory::CreatePlayer(m_registry); //when create entity > entity added to m_added
}

void Scene::Update(float deltaTime)
{
    m_registry.Update(deltaTime); //entities in m_added added to relevant system
}

void Scene::Render()
{
    m_registry.Render(m_renderer);
}

void Scene::Shutdown()
{

}
