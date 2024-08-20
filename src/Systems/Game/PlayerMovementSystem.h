#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../../ECS/ECS.h"
#include <glm/glm.hpp>
#include "../../Events/EventData.h"

class PlayerMovementSystem : public System
{
public:
    PlayerMovementSystem();

    void Init() override;
    void Move(glm::vec3& value, float dt = 0.f);

    void OnHitWall(CollisionData& data);
    void OnWalkablePath(CollisionData& data);

    Entity GetPlayer(CollisionData& data);
};

#endif