#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

struct AnimationComponent
{
    size_t numOfFrame, numOfAnims, currentFrame, frameSpeed;
    bool isLooping;
    bool endOfSprite;

    AnimationComponent(size_t numFrame = 1, size_t numAnim = 1, size_t fSpeed = 1)
        : numOfFrame(numFrame), numOfAnims(numAnim), currentFrame(0), frameSpeed(fSpeed)
    {
        
    }
};

#endif