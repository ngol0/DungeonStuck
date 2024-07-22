#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

class Entity;

struct TransformComponent
{
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    TransformComponent(glm::vec2 position, glm::vec2 scale, float rotation) : position(position), scale(scale), rotation(rotation)
    {
        
    }
};

#endif
