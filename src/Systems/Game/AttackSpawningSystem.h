#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "../../ECS/ECS.h"

class AttackSpawningSystem : public System
{
private:
    //bool m_isAttacking;
    //float m_timer;

public:
    AttackSpawningSystem();

    //void Init() override;
    void Update(float dt) override;

    void Attack(int& weaponType);
};

#endif