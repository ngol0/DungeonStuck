#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include <glm/glm.hpp>

class PlayerMovementSystem : public System
{
public:
    PlayerMovementSystem();
    void Move(glm::vec3& value);
};

#endif