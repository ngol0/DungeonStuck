#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include <map>

class CollisionSystem : public System
{
private:
    std::map<std::pair<Entity, Entity>, bool> collision_map;

public:
    CollisionSystem();

    void Update(float dt) override;
};

#endif