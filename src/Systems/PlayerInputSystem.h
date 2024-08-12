#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include "../ECS/ECS.h"

class PlayerInputSystem : public System
{
private:
    

public:
    PlayerInputSystem();

    void Init() override;
    void Update(float dt) override {};
};

#endif