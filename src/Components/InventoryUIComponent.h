#ifndef INVENTORYSLOTCOMPONENT_H
#define INVENTORYSLOTCOMPONENT_H

struct InventoryUIComponent
{
    int slotIndex;
    
    InventoryUIComponent(int index = 0) : slotIndex(index) {}
};

#endif