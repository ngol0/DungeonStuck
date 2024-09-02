#ifndef ENEMYAISYSTEM_H
#define ENEMYAISYSTEM_H

#include "../../ECS/ECS.h"

class EnemyAISystem : public System
{
private:
    

public:
    EnemyAISystem();

    void Init() override;
    void Update(float dt) override {};
};

#endif