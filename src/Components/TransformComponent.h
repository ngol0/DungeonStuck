#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    glm::vec2 prevPos;

    TransformComponent() : position(glm::vec2{0.f}), scale(glm::vec2{1.f}), rotation(0.f) {}

    TransformComponent(glm::vec2 pos, glm::vec2 scl, float rot) : position(pos), scale(scl), rotation(rot) {}
};

#endif
