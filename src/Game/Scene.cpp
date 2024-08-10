#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DebugColliderSystem.h"
#include "../Events/EventType.h"

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
    Registry::GetInstance().AddSystem<CollisionSystem>();
    Registry::GetInstance().AddSystem<DebugColliderSystem>();
   
    //Create entity
    EntityFactory::CreateTank(); //when create entity > entity added to m_added
    EntityFactory::CreateChopper();
    EntityFactory::CreateTank2(); 

    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionEnter, this, &Scene::Test);
    EventManager::GetInstance().Register<CollisionData>(EventType::OnCollisionExit, this, &Scene::Test2);
}

void Scene::Test(CollisionData& data)
{
    spdlog::info("Testing call, collision ENTER between: " + 
        std::to_string(data.collisionPair.first) + " and " + std::to_string(data.collisionPair.second));
}

void Scene::Test2(CollisionData& data)
{
    spdlog::info("Testing call 2, collision EXIT between: " + 
        std::to_string(data.collisionPair.first) + " and " + std::to_string(data.collisionPair.second));
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
