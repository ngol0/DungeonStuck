#include "Scene.h"
#include "EntityFactory.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/HUDSystem.h"
#include "../Systems/Game/DamageSystem.h"
#include "../Systems/Game/PlayerInputSystem.h"
#include "../Systems/Game/PlayerActionSystem.h"
#include "../Systems/Game/AttackSpawningSystem.h"
#include "../Systems/Game/WeaponActionSystem.h"
#include "../Systems/Game/ItemCollectSystem.h"
#include "../Systems/Game/InventorySystem.h"
#include "../Systems/Game/InventoryUISystem.h"
#include "../Systems/Game/EnemyAISystem.h"
#include "../Systems/Editor/InputEditorSystem.h"
#include "../Systems/Editor/EnemySpawnEditor.h"

#include "../Asset/AssetManager.h"

#include "../Components/SpriteComponent.h"

#include <glm/glm.hpp>

SDL_Rect Scene::camera{0, 0, 800, 600};
bool Scene::isDebugging{false};

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
    Registry::GetInstance().AddSystem<HUDSystem>();
    Registry::GetInstance().AddSystem<CollisionSystem>();

    //game
    Registry::GetInstance().AddSystem<DamageSystem>();
    Registry::GetInstance().AddSystem<PlayerActionSystem>();
    Registry::GetInstance().AddSystem<AttackSpawningSystem>();
    Registry::GetInstance().AddSystem<WeaponActionSystem>();
    Registry::GetInstance().AddSystem<EnemyAISystem>();
    Registry::GetInstance().AddSystem<ItemCollectSystem>();
    Registry::GetInstance().AddSystem<InventorySystem>();
    Registry::GetInstance().AddSystem<InventoryUISystem>();

    //input system
    Registry::GetInstance().AddSystem<PlayerInputSystem>(); //system to bind all the input -- should be added last
    //input editor
    Registry::GetInstance().AddSystem<InputEditorSystem>();
    Registry::GetInstance().AddSystem<EnemySpawnEditor>();


    // //----------------------------------------Create entity----------------------------------------
    EntityFactory::CreateItem(glm::vec2(100.f, 100.f), ItemType::HEALTH_PORTION, false);
    EntityFactory::CreateItem(glm::vec2(100.f, 300.f), ItemType::HEALTH_PORTION, false);

    // create player
    EntityFactory::CreatePlayer(glm::vec2(0.f, 1.f));

    // create slime enemy for testing the combat
    EntityFactory::CreateEnemy(glm::vec2(1.f, 200.f), glm::vec2(1.f, 0.f), EnemyType::SLIME);

    // game UI - TODO: refactor to call this somewhere else
    for (int i = 0; i < 2; ++i)
    {
        EntityFactory::CreateInventorySlotUI(glm::vec2{0.f + i * 50.f, 0.f});
        EntityFactory::CreateInventoryItemUI(glm::vec2{0.f + i * 20.f, 8.f}, ItemType::NONE, i);
    }
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
    //--map
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::MAP, "./assets/tilemaps/tilemap_packed.png");

    //--game
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::PLAYER, "./assets/images/player.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::SLIME, "./assets/images/slime.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::HEALTH_ITEM, "./assets/images/basic_weapon.png"); //todo: change sprite

    //--UI
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::UI_SLOT_INVENTORY, "./assets/images/ui-slot.png");
}
