#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <glm/glm.hpp>

struct HealthComponent
{
    float healthAmount;
    HealthComponent(float amt = 1) : healthAmount(amt) {}
};

#endif