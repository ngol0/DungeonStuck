#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct BoxColliderComponent
{
    std::string tag;
    int width;
    int height;

    BoxColliderComponent(const std::string& tag = "", int w = 0, int h = 0) : tag(tag), width(w), height(h)
    {
        
    }
};

#endif