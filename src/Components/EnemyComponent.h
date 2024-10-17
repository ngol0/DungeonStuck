#ifndef ENEMYCOMPONENT_H
#define ENEMYCOMPONENT_H

#include "../Global/GlobalDataType.h"

struct EnemyComponent
{
    EnemyType enemType;
    EnemyComponent(EnemyType type = EnemyType::SLIME) : enemType(type) {};
};

#endif