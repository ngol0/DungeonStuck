#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class InventorySystem : public System
{
private:
    

public:
    InventorySystem();

    void Init() override;
    void Update(float dt) override;

    void OnItemCollected(ItemEventData& data);
    void OnKeyPressed(KeyPressedEventData& data);

    void UseItem(ItemType type);
};

#endif

