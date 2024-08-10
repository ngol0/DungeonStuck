#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Events/EventData.h"

class DamageSystem : public System
{
private:
    

public:
    DamageSystem();

    void Init() override;
    void Update(float dt) override {};
    void OnCollisionHappen(CollisionData& data);

    //collision response
    void DamageTakenBy(Entity& victim, float damageAmount, CollisionData& data);
};

#endif