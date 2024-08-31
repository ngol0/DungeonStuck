#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "../../ECS/ECS.h"

class WeaponSpawningSystem : public System
{
private:
    //bool m_isAttacking;
    //float m_timer;

public:
    WeaponSpawningSystem();

    //void Init() override;
    void Update(float dt) override;

    void Attack(int& weaponType);
};

#endif