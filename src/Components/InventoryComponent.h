#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include "../Events/EventData.h"

struct InventoryComponent
{
    const static int NUM_OF_SLOT = 2;
    //an array of slots
    ItemEventData inventory[NUM_OF_SLOT];
    
    InventoryComponent() = default;
};

#endif