#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <utility>
#include <SDL2/SDL_image.h>

struct IData
{
    virtual ~IData() = default;
};

struct CollisionData : public IData
{
    std::pair<int, int> collisionPair;

    virtual ~CollisionData() = default;
    CollisionData(std::pair<int,int> pair) : collisionPair(pair) {}
};

#endif