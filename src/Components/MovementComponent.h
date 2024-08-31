#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <glm/glm.hpp>

struct MovementComponent
{
    float speed;
    glm::vec2 moveDirection;
    glm::vec2 lastDirection;
    
    MovementComponent(float speed = 0, glm::vec2 moveDir = glm::vec2{1.0f, 0.f}) : speed(speed), moveDirection(moveDir)
    {
        
    }
};

#endif