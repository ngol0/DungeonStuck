#ifndef INVENTORYSLOTCOMPONENT_H
#define INVENTORYSLOTCOMPONENT_H

struct InventorySlotComponent
{
    int slotIndex;
    
    InventorySlotComponent(int index = 0) : slotIndex(index) {}
};

#endif