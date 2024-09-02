#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H

#include "../Global/GlobalDataType.h"

struct WeaponComponent
{
    WeaponComponent(float dmg, float timeE) : damage(dmg), endTime(timeE)
    {
        
    }

    float damage;
    float endTime;
    float timer{0.f};
};

#endif