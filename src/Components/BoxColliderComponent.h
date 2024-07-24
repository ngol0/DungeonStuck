#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

struct BoxColliderComponent
{
    BoxColliderComponent()
    {
        spdlog::info("BoxCollider Component created");
    }
};

#endif