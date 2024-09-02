#ifndef PROJECTILECYCLESYSTEM_H
#define PROJECTILECYCLESYSTEM_H

#include "../../ECS/ECS.h"


class WeaponActionSystem : public System
{
public:
    WeaponActionSystem();

    void Init() override;
    void Update(float dt) override;
};

#endif