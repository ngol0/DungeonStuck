#include "InventoryUISystem.h"

#include "../../Components/InventoryUIComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/TextComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

#include "../../Game/EntityFactory.h"

InventoryUISystem::InventoryUISystem()
{
    RequireComponent<InventoryUIComponent>();
}

void InventoryUISystem::Init()
{
    EventManager::GetInstance().Register<InventoryItemEventData>(
        EventType::OnNewItemAdded, this, &InventoryUISystem::OnNewItemAdded);

    EventManager::GetInstance().Register<InventoryItemEventData>(
        EventType::OnItemAmountChanged, this, &InventoryUISystem::OnInventoryChanged);
}

void InventoryUISystem::OnNewItemAdded(InventoryItemEventData &data)
{
    for (auto &e : GetSystemEntities())
    {
        auto &inventoryUI = e.GetComponent<InventoryUIComponent>();
        if (inventoryUI.slotIndex == data.slot)
        {
            // update item ui
            auto &ui = e.GetComponent<UIComponent>();
            auto &amtlabel = e.GetComponent<TextComponent>();

            switch (data.itemType)
            {
            case ItemType::HEALTH_PORTION:
                ui.assetId = SpriteId::HEALTH_ITEM;
                break;

            case ItemType::STRENTH_PORTION:
                ui.assetId = SpriteId::STRENGTH_ITEM;
                break;

            default:
                // Optionally handle other cases or leave empty if not needed
                break;
            }

            ui.texture = AssetManager::GetInstance().GetTexture(ui.assetId);
            int w, h;
            SDL_QueryTexture(ui.texture, NULL, NULL, &w, &h);
            ui.srcRect = {0, 0, w, h};

            std::string amountText = std::to_string(data.amount);
            amtlabel.text = amountText;
        }
    }
}

void InventoryUISystem::OnInventoryChanged(InventoryItemEventData &data)
{
    for (auto &e : GetSystemEntities())
    {
        auto &inventoryUI = e.GetComponent<InventoryUIComponent>();
        if (inventoryUI.slotIndex == data.slot)
        {
            // update item ui
            auto &ui = e.GetComponent<UIComponent>();
            auto &amtlabel = e.GetComponent<TextComponent>();
            if (data.amount == 0)
            {
                ui.assetId = SpriteId::NONE;
                ui.texture = AssetManager::GetInstance().GetTexture(ui.assetId);

                amtlabel.text = "";
            }
            else
            {
                std::string amountText = std::to_string(data.amount);
                amtlabel.text = amountText;
            }
        }
    }
}
