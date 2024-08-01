#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"

#include "../Global/AssetManager.h"

#include <spdlog/spdlog.h>

void Scene::Init(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    //load asset??
    //todo: figure out where should assets be loaded and when?
    AssetManager::GetInstance().LoadTextureAsset(renderer);

    //Create system
    Registry::GetInstance().AddSystem<MovementSystem>();
    Registry::GetInstance().AddSystem<AnimationSystem>();
    Registry::GetInstance().AddSystem<RenderSystem>();
   
    //Create entity
    EntityFactory::CreatePlayer(); //when create entity > entity added to m_added
    EntityFactory::CreateChopper();
}

void Scene::Update(float deltaTime)
{
    Registry::GetInstance().Update(deltaTime); //entities in m_added added to relevant system
}

void Scene::Render()
{
    Registry::GetInstance().Render(m_renderer);
}

void Scene::Clear()
{
    
}
