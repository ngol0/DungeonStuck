#ifndef PATHNODECOMPONENT_H
#define PATHNODECOMPONENT_H

#include <glm/glm.hpp>
#include "../Global/Utils.h"

struct PathNodeComponent
{
    GridPosition gridPos;
    int camefromEntityId = -1;
    PathNodeComponent* parentNode;
    
    int r = 255;
    int g = 255;
    int b = 0;

    //cost for path finding
    int fCost = 0;
    int gCost = 0;
    int hCost = 0;

    bool isWalkable = false;
    
    PathNodeComponent(GridPosition pos) : gridPos(pos)
    {
       
    }

    // Comparator for priority queue to get the lowest fCost
    bool operator>(const PathNodeComponent& other) const 
    {
        return fCost > other.fCost;
    }
};

#endif