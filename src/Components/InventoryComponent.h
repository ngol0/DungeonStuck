#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <glm/glm.hpp>

#include "../Events/EventData.h"

struct InventoryComponent
{
    //an array of slots
    ItemData inventory[2];
    
    InventoryComponent() = default;
};

#endif