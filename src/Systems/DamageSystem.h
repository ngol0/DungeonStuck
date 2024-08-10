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
    void RegisterToEvent();
    void OnCollisionHappen(CollisionData& data);

    //collision response
    void OnEnemyCollidePlayer(int playerId);
    void OnPlayerBulletCollideEnemy(int enemyId);
    void OnEnemyBulletCollidePlayer(int playerId);
};

#endif