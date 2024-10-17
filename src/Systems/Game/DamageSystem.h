#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class DamageSystem : public System
{
private:
    

public:
    DamageSystem();

    void Init() override;
    void Update(float dt) override {};
    void OnCollisionHappen(CollisionEventData& data);

    //collision response
    void DamageTakenBy(Entity& victim, float damageAmount, CollisionEventData& data);
};

#endif