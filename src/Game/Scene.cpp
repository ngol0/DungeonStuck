#include "Scene.h"
#include "EntityFactory.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/Game/DamageSystem.h"
#include "../Systems/Game/PlayerInputSystem.h"
#include "../Systems/Game/PlayerMovementSystem.h"
#include "../Systems/Editor/InputEditorSystem.h"

#include "../Asset/AssetManager.h"

#include "../Components/SpriteComponent.h"

#include <glm/glm.hpp>

SDL_Rect Scene::camera{0, 0, 800, 600};

void Scene::Init(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    //load asset??
    //todo: figure out where should assets be loaded and when?
    LoadTextureAsset();
    AssetManager::GetInstance().OpenMapFile("./assets/tilemaps/withbox.map");

    //----------------------------------------Create system----------------------------------------
    //engine
    Registry::GetInstance().AddSystem<CameraMovementSystem>();
    Registry::GetInstance().AddSystem<AnimationSystem>();
    Registry::GetInstance().AddSystem<RenderSystem>();
    Registry::GetInstance().AddSystem<CollisionSystem>();

    //game
    Registry::GetInstance().AddSystem<DamageSystem>();
    Registry::GetInstance().AddSystem<PlayerMovementSystem>();

    //input system
    Registry::GetInstance().AddSystem<PlayerInputSystem>(); //system to bind all the input -- should be added last
    //input editor
    Registry::GetInstance().AddSystem<InputEditorSystem>();


    // //----------------------------------------Create entity----------------------------------------
    EntityFactory::CreatePlayer(glm::vec2(0.f, 1.f));
    //EntityFactory::CreateEnemy(glm::vec2(300.f, 1.f), -50.f, 100.f); //todo: enemy type for diff params
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

void Scene::LoadTextureAsset()
{
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::TANK, "./assets/images/tank-panther-right.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::PLAYER, "./assets/images/zombie-full.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::MAP, "./assets/tilemaps/tilemap_packed.png");
}
