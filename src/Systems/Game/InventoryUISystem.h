#ifndef INVENTORYUISYSTEM_H
#define INVENTORYUISYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class InventoryUISystem : public System
{
public:
    InventoryUISystem();

    void Init() override;
    void Update(float dt) override {};

    void OnNewItemAdded(InventoryItemEventData& data);
    void OnInventoryChanged(InventoryItemEventData& data);
};

#endif

