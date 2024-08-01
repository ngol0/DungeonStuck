#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"

class AnimationSystem : public System
{
public:
    AnimationSystem();
    
    void Update(float dt) override;
};

#endif