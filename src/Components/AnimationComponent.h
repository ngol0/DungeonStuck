#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <glm/glm.hpp>

struct AnimationComponent
{
    size_t numOfFrame, numOfAnims, currentFrame, frameSpeed;

    AnimationComponent(size_t numFrame = 1, size_t numAnim = 1, size_t fSpeed = 1)
        : numOfFrame(numFrame), numOfAnims(numAnim), currentFrame(0), frameSpeed(fSpeed)
    {
        
    }
};

#endif