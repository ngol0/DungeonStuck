#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <glm/glm.hpp>

struct MovementComponent
{
    glm::vec2 moveDirection;
    float speed;

    MovementComponent(float speed = 0) : moveDirection(glm::vec2(1.0f, 0.0f)), speed(speed)
    {
        
    }
};

#endif