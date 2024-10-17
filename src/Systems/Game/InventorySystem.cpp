#include "InventorySystem.h"

#include "../../Components/InventoryComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include "../../Game/EntityFactory.h"

InventorySystem::InventorySystem()
{
    RequireComponent<InventoryComponent>();
}

void InventorySystem::Init()
{
    EventManager::GetInstance().Register<ItemData>(EventType::OnItemCollected, this, &InventorySystem::OnItemCollected);
}

void InventorySystem::OnItemCollected(ItemData &data)
{
    // Entity item = EntityFactory::CreateItem(glm::vec2{0.f}, data.itemType);

    for (auto &e : GetSystemEntities())
    {
        auto &inventoryComp = e.GetComponent<InventoryComponent>();

        // todo: check if there's a space
        // if not > ask to replace?
        inventoryComp.inventory[0] = data;
    }
}

void InventorySystem::OnKeyPressed(KeyPressedData &data)
{
    // if press 1 > use first item
    if (data.key == SDLK_1)
    {
        for (auto &e : GetSystemEntities())
        {
            auto &inventoryComp = e.GetComponent<InventoryComponent>();
            ItemData data = inventoryComp.inventory[0];

            //use the item
            
        }
    }
    // if press 2 > use second item
    if (data.key == SDLK_2)
    {
        for (auto &e : GetSystemEntities())
        {
            auto &inventoryComp = e.GetComponent<InventoryComponent>();
            ItemData data = inventoryComp.inventory[1];

            //use the item
        }
    }
}

void InventorySystem::Update(float dt)
{
}
