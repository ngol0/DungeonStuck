#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

struct TransformComponent
{
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    TransformComponent() : position(glm::vec2{0.f}), scale(glm::vec2{1.f}), rotation(0.f)
    {
        //spdlog::info("Transform Component created with rotation: " + std::to_string(rotation));
    }

    TransformComponent(glm::vec2 pos, glm::vec2 scl, float rot) : position(pos), scale(scl), rotation(rot)
    {
        spdlog::info("Transform Component created with rotation: " + std::to_string(rotation));
    }
};

#endif
