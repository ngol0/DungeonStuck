#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include <map>

class CollisionSystem : public System
{
private:
    std::map<std::pair<int, int>, bool> m_collisionMap;

public:
    CollisionSystem();

    void Update(float dt) override;
};

#endif