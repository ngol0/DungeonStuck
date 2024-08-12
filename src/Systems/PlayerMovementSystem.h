#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include <glm/glm.hpp>

class PlayerMovementSystem : public System
{
public:
    PlayerMovementSystem();

    void Update(float dt) override;
    void Move(glm::vec2& value);
};

#endif