#include "InventoryUISystem.h"

#include "../../Components/InventorySlotComponent.h"
#include "../../Components/SpriteComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include "../../Game/EntityFactory.h"

InventoryUISystem::InventoryUISystem()
{
    RequireComponent<InventorySlotComponent>();
}

void InventoryUISystem::Init()
{
    EventManager::GetInstance().Register<InventoryItemEventData>(
        EventType::OnNewItemAdded, this, &InventoryUISystem::OnNewItemAdded);

    EventManager::GetInstance().Register<InventoryItemEventData>(
        EventType::OnInventoryChanged, this, &InventoryUISystem::OnInventoryChanged);
}

void InventoryUISystem::OnNewItemAdded(InventoryItemEventData &data)
{
    for (auto &e : GetSystemEntities())
    {
        auto &inventoryUI = e.GetComponent<InventorySlotComponent>();
        if (inventoryUI.slotIndex == data.slot)
        {
            // update ui
            auto &ui = e.GetComponent<UIComponent>();

            if (data.itemType == ItemType::HEALTH_PORTION)
            {
                ui.assetId = SpriteId::HEALTH_ITEM;
            }

            if (data.itemType == ItemType::STRENTH_PORTION)
            {
                ui.assetId = SpriteId::STRENGTH_ITEM;
            }

            ui.texture = AssetManager::GetInstance().GetTexture(ui.assetId);
            int w, h;
            SDL_QueryTexture(ui.texture, NULL, NULL, &w, &h);
            ui.srcRect = {0, 0, w, h};
        }
    }
}

void InventoryUISystem::OnInventoryChanged(InventoryItemEventData &data)
{
    
}
