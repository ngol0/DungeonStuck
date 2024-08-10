#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <utility>

struct IData
{
    virtual ~IData() = default;
};

struct CollisionData : public IData
{
    virtual ~CollisionData() = default;

    std::pair<int, int> collisionPair;

    CollisionData(std::pair<int,int> pair) : collisionPair(pair) {}
};

#endif