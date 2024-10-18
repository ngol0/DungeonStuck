#ifndef HEALTHUISYSTEM_H
#define HEALTHUISYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class HealthUISystem : public System
{
public:
    HealthUISystem();

    void Init() override;
    void Update(float dt) override {};

    void OnPlayerHealed(HealthData& data);
};

#endif

