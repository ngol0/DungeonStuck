#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

struct HealthComponent
{
    float healthAmount;
    HealthComponent(float amt = 1) : healthAmount(amt) {}
};

#endif