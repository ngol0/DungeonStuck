#include "Scene.h"
#include "EntityFactory.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/HUDSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/Game/DamageSystem.h"
#include "../Systems/Game/PlayerInputSystem.h"
#include "../Systems/Game/PlayerActionSystem.h"
#include "../Systems/Game/AttackSpawningSystem.h"
#include "../Systems/Game/WeaponActionSystem.h"
#include "../Systems/Game/ItemCollectSystem.h"
#include "../Systems/Game/InventorySystem.h"
#include "../Systems/Game/InventoryUISystem.h"
#include "../Systems/Game/HealthUISystem.h"
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
    Registry::GetInstance().AddSystem<RenderTextSystem>();
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
    Registry::GetInstance().AddSystem<HealthUISystem>();

    //input system
    Registry::GetInstance().AddSystem<PlayerInputSystem>(); //system to bind all the input -- should be added last
    //input editor
    Registry::GetInstance().AddSystem<InputEditorSystem>();
    Registry::GetInstance().AddSystem<EnemySpawnEditor>();


    // //----------------------------------------Create entity----------------------------------------
    EntityFactory::CreateItem(glm::vec2(100.f, 100.f), ItemType::HEALTH_PORTION);
    EntityFactory::CreateItem(glm::vec2(200.f, 300.f), ItemType::HEALTH_PORTION);

    EntityFactory::CreateItem(glm::vec2(100.f, 500.f), ItemType::STRENTH_PORTION);
    EntityFactory::CreateItem(glm::vec2(300.f, 750.f), ItemType::STRENTH_PORTION);

    // create player
    EntityFactory::CreatePlayer(glm::vec2(0.f, 1.f));

    // create slime enemy for testing the combat
    EntityFactory::CreateEnemy(glm::vec2(1.f, 200.f), glm::vec2(1.f, 0.f), EnemyType::SLIME);

    // ***-----TODO: refactor to call this somewhere else
    // game UI - inventory UI
    for (int i = 0; i < 2; ++i)
    {
        EntityFactory::CreateInventorySlotUI(glm::vec2{750.f - i * 50.f, 10.f});
        EntityFactory::CreateInventoryItemUI(glm::vec2{760.f - i * 50.f, 18.f}, ItemType::NONE, i);
    }
    // player health ui
    EntityFactory::CreateHealthUI(glm::vec2{5.f, 5.f});
}

void Scene::Update(float deltaTime)
{
    Registry::GetInstance().Update(deltaTime); //entities in m_added added to relevant system
}

void Scene::Render()
{
    //Registry::GetInstance().Render(m_renderer);

    Registry::GetInstance().GetSystem<RenderSystem>().Render(m_renderer);
    Registry::GetInstance().GetSystem<HUDSystem>().Render(m_renderer);
    Registry::GetInstance().GetSystem<RenderTextSystem>().Render(m_renderer);
}

void Scene::Clear()
{
    
}

void Scene::LoadTextureAsset()
{
    //-------------------------------Sprite-------------------------------//
    //--map
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::MAP, "./assets/tilemaps/tilemap_packed.png");

    //--game
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::PLAYER, "./assets/images/player.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::SLIME, "./assets/images/slime.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::CHEST, "./assets/images/chest.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::HEALTH_ITEM, "./assets/images/health-portion.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::STRENGTH_ITEM, "./assets/images/strength-portion.png");

    //--UI
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::UI_SLOT_INVENTORY, "./assets/images/ui-slot.png");
    AssetManager::GetInstance().AddSprite(m_renderer, SpriteId::UI_HEALTH, "./assets/images/heart.png");

    //-------------------------------Font-------------------------------//
    AssetManager::GetInstance().AddFont(SpriteId::STANDARD_TEXT, "./assets/fonts/charriot.ttf", 15);
    AssetManager::GetInstance().AddFont(SpriteId::OTHER_TEXT, "./assets/fonts/charriot.ttf", 30);
}
