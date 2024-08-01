#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct BoxColliderComponent
{
    std::string tag;
    int width;
    int height;
    glm::vec2 offset;

    BoxColliderComponent(const std::string& tag = "", int w = 0, int h = 0, glm::vec2 offset = glm::vec2(0.f)) 
        : tag(tag), width(w), height(h), offset(offset)
    {
        
    }
};

#endif