#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

struct HealthComponent
{
    int healthAmount;
    HealthComponent(int amt = 1) : healthAmount(amt) {}
};

#endif