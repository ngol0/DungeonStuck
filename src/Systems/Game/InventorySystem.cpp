#include "InventorySystem.h"

#include "../../Components/InventoryComponent.h"
#include "../../Components/HealthComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

InventorySystem::InventorySystem()
{
    RequireComponent<InventoryComponent>();
}

void InventorySystem::Init()
{
    EventManager::GetInstance().Register<ItemEventData>(EventType::OnItemCollected, this, &InventorySystem::OnItemCollected);
    EventManager::GetInstance().Register<KeyPressedEventData>(EventType::OnKeyPressed, this, &InventorySystem::OnKeyPressed);
}

void InventorySystem::OnItemCollected(ItemEventData &data)
{
    // Entity item = EntityFactory::CreateItem(glm::vec2{0.f}, data.itemType);
    for (auto &e : GetSystemEntities())
    {
        auto &inventoryComp = e.GetComponent<InventoryComponent>();

        // check inventory to see if item already exists
        for (int i = 0; i < InventoryComponent::NUM_OF_SLOT; ++i)
        {
            if (inventoryComp.inventory[i].itemType == data.itemType)
            {
                inventoryComp.inventory[i].amount += data.amount;
                data.amount = 0;
                spdlog::info("Added more item into existing one, current amount: " + std::to_string(inventoryComp.inventory[i].amount));

                //event to update ui
                EventManager::GetInstance().Notify<InventoryItemEventData>
                (
                    EventType::OnInventoryChanged, 
                    InventoryItemEventData(inventoryComp.inventory[i].itemType, inventoryComp.inventory[i].amount, i)
                );

                break;
            }
        }
        //if not, add item into an empty slot
        if (data.amount > 0)
        {
            spdlog::info("Adding item to new slot");
            for (int i = 0; i < InventoryComponent::NUM_OF_SLOT; ++i)
            {
                if (inventoryComp.inventory[i].itemType == ItemType::NONE)
                {
                    inventoryComp.inventory[i] = data;

                    //event to update ui
                    EventManager::GetInstance().Notify<InventoryItemEventData>
                    (
                        EventType::OnNewItemAdded,
                        InventoryItemEventData(inventoryComp.inventory[i].itemType, inventoryComp.inventory[i].amount, i)
                    );

                    break;
                }
            }
        }

        spdlog::info("Item Collected");
    }
}

void InventorySystem::OnKeyPressed(KeyPressedEventData &data)
{
    // if press 1 > use first item
    if (data.key == SDLK_1)
    {
        for (auto &e : GetSystemEntities())
        {
            auto& inventoryComp = e.GetComponent<InventoryComponent>();
            if (inventoryComp.inventory[0].amount == 0) return;
            UseItem(inventoryComp.inventory[0].itemType);
            inventoryComp.inventory[0].amount -= 1;

            //event to update ui

        }
    }
    // if press 2 > use second item
    else if (data.key == SDLK_2)
    {
        for (auto &e : GetSystemEntities())
        {
            auto &inventoryComp = e.GetComponent<InventoryComponent>();
            if (inventoryComp.inventory[1].amount == 0) return;
            UseItem(inventoryComp.inventory[1].itemType);
            inventoryComp.inventory[1].amount -= 1;

            //event to update ui

        }
    }
}

void InventorySystem::UseItem(ItemType itemType)
{
    // use the item
    for (auto &e : GetSystemEntities())
    {
        if (itemType == ItemType::HEALTH_PORTION)
        {
            // get player's health
            auto &healthComp = e.GetComponent<HealthComponent>();
            healthComp.healthAmount += 1;
            spdlog::info("Player health: " + std::to_string(healthComp.healthAmount));
        }
        if (itemType == ItemType::STRENTH_PORTION)
        {

        }
    }
}

void InventorySystem::Update(float dt)
{
}
