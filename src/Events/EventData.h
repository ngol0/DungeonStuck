#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <utility>
#include <SDL2/SDL_image.h>
#include "../Global/Interface.h"

struct CollisionData : public IData
{
    std::pair<int, int> collisionPair;
    SDL_Rect overlap;
    float dt;

    virtual ~CollisionData() = default;
    CollisionData(std::pair<int,int> pair, SDL_Rect rect, float d) : collisionPair(pair), overlap(rect), dt(d) {}
};

#endif