#include "Scene.h"
#include "../Entity/EntityFactory.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DebugColliderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/PlayerInputSystem.h"

#include "../Events/EventType.h"
#include "../Asset/AssetManager.h"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>


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
    Registry::GetInstance().AddSystem<DamageSystem>();
    Registry::GetInstance().AddSystem<PlayerInputSystem>();
   
    //Create entity
    EntityFactory::CreatePlayer(glm::vec2(0.f, 1.f));
    EntityFactory::CreateEnemy(glm::vec2(300.f, 1.f), -50.f, 100.f); //todo: enemy type for diff params
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
