#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct HealthComponent
{
    float healthAmount;
    HealthComponent(float amt = 1) : healthAmount(amt) {}
};

#endif