#ifndef PROJECTILECYCLESYSTEM_H
#define PROJECTILECYCLESYSTEM_H

#include "../../ECS/ECS.h"


class ProjectileActionSystem : public System
{
public:
    ProjectileActionSystem();

    void Init() override;
    void Update(float dt) override;
};

#endif