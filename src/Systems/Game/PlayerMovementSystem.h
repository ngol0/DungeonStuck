#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../../ECS/ECS.h"
#include <glm/glm.hpp>
#include "../../Events/EventData.h"

class PlayerMovementSystem : public System
{
private:
    void OnHitWall(CollisionData& data);
    void OnAwayFromWall(CollisionData& data);

    float variable{1.f};

public:
    PlayerMovementSystem();

    void Init() override;
    void Move(glm::vec3& value, float dt = 0.f);

    void Update(float dt) override;
};

#endif