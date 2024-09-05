#include "Scene.h"
#include "EntityFactory.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/Game/DamageSystem.h"
#include "../Systems/Game/PlayerInputSystem.h"
#include "../Systems/Game/PlayerActionSystem.h"
#include "../Systems/Game/AttackSpawningSystem.h"
#include "../Systems/Game/WeaponActionSystem.h"
#include "../Systems/Game/EnemyAISystem.h"
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
    AssetManager::GetInstance().OpenMapFile("./assets/tilemaps/fixed_map.map");

    //----------------------------------------Create system----------------------------------------
    //engine
    Registry::GetInstance().AddSystem<CameraMovementSystem>();
    Registry::GetInstance().AddSystem<AnimationSystem>();
    Registry::GetInstance().AddSystem<RenderSystem>();
    Registry::GetInstance().AddSystem<CollisionSystem>();

    //game
    Registry::GetInstance().AddSystem<DamageSystem>();
    Registry::GetInstance().AddSystem<PlayerActionSystem>();
    Registry::GetInstance().AddSystem<AttackSpawningSystem>();
    Registry::GetInstance().AddSystem<WeaponActionSystem>();
    Registry::GetInstance().AddSystem<EnemyAISystem>();

    //input system
    Registry::GetInstance().AddSystem<PlayerInputSystem>(); //system to bind all the input -- should be added last
    //input editor
    Registry::GetInstance().AddSystem<InputEditorSystem>();


    // //----------------------------------------Create entity----------------------------------------
    // create player
    EntityFactory::CreatePlayer(glm::vec2(0.f, 1.f));

    // create slime enemy for testing the combat
    EntityFactory::CreateEnemy(glm::vec2(1.f, 200.f), EnemyType::SLIME); //todo: enemy type for diff params
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
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::MAP, "./assets/tilemaps/tilemap_packed.png");

    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::PLAYER, "./assets/images/player.png");
    //AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::BASIC_WEAPON, "./assets/images/basic_weapon.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::SLIME, "./assets/images/slime.png");
}
