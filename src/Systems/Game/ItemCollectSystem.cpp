#include "ItemCollectSystem.h"

#include "../../Components/ItemComponent.h"
#include "../../Components/BoxColliderComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

ItemCollectSystem::ItemCollectSystem()
{
    RequireComponent<ItemComponent>();
}

void ItemCollectSystem::Init()
{
    //listen to collision event to see if item can be collected
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnCollisionEnter, this, &ItemCollectSystem::OnNearItem);
    EventManager::GetInstance().Register<CollisionEventData>(EventType::OnCollisionExit, this, &ItemCollectSystem::OnExitItem);
}

Entity ItemCollectSystem::FindItem(CollisionEventData& data)
{
    auto &collider1 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.first);
    auto &collider2 = Registry::GetInstance().GetComponent<BoxColliderComponent>(data.collisionPair.second);

    int itemId = -1;

    if (collider1.tag == Tag::ITEM && collider2.tag == Tag::PLAYER)
    {
        itemId = data.collisionPair.first;
    }
    else if (collider1.tag == Tag::PLAYER && collider2.tag == Tag::ITEM)
    {
        itemId = data.collisionPair.second;
    }

    Entity item(itemId);
    return item;
}

void ItemCollectSystem::OnNearItem(CollisionEventData& data)
{
    Entity item = FindItem(data);
    if (item.GetId() == -1) return;

    spdlog::info("Player collides with item!");

    auto& itemComponent = item.GetComponent<ItemComponent>();
    itemComponent.canCollect = true;
}

void ItemCollectSystem::OnExitItem(CollisionEventData& data)
{
    Entity item = FindItem(data);
    if (item.GetId() == -1) return;

    auto& itemComponent = item.GetComponent<ItemComponent>();
    itemComponent.canCollect = false;
}

void ItemCollectSystem::Update(float dt)
{
}

void ItemCollectSystem::CollectItem(int& data)
{
    // put the item in inventory
    for (auto &e : GetSystemEntities())
    {
        auto& itemComponent = e.GetComponent<ItemComponent>();
        if (itemComponent.canCollect)
        {
            ItemEventData itemData(itemComponent.itemType, itemComponent.amount);
            // trigger an event for inventory system to register the item
            EventManager::GetInstance().Notify<ItemEventData>(EventType::OnItemCollected, itemData);

            // set the item on scene to be inactive
            e.Destroy();
        }
    }
}