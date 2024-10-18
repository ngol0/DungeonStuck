#ifndef ENEMYAISYSTEM_H
#define ENEMYAISYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class EnemyAISystem : public System
{
private:
    

public:
    EnemyAISystem();

    void Init() override;
    void Update(float dt) override;

    void OnHitWall(CollisionEventData& data);
    void OnAwayFromWall(CollisionEventData& data);

    void OnEnemyDieAnim(Entity& victim);
    void OnEnemyDestroy(Entity& victim);
};

#endif