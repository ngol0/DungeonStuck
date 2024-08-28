#ifndef CAMERAFOLLOWSYSTEM_H
#define CAMERAFOLLOWSYSTEM_H

#include "../ECS/ECS.h"

class CameraMovementSystem : public System
{
public:
    CameraMovementSystem();

    //void Init() override;
    void Update(float dt) override;
};

#endif