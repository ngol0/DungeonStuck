#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

#include "../Global/GlobalDataType.h"

struct ItemComponent
{    
    ItemType itemType;
    int amount;

    bool canCollect = false;
    bool hasBeenCollected = false;
    ItemComponent(ItemType type = ItemType::NONE, int num = 1) : itemType(type), amount(num) {} 
};

#endif