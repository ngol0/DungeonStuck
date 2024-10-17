#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

#include <glm/glm.hpp>
#include "../Global/GlobalDataType.h"

struct ItemComponent
{    
    ItemType type;

    bool canCollect = false;
    bool hasBeenCollected = false;
    ItemComponent() = default;
};

#endif