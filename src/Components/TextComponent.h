#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL.h>

struct TextComponent
{
    glm::vec2 position;
    std::string text;
    std::string id;
    SDL_Color color;

    bool isFixed;
    bool isActive;

    TextComponent
    (
        glm::vec2 pos = glm::vec2{0.f}, 
        const std::string& text = "", 
        const std::string& id = "", 
        const SDL_Color& color = {0,0,0,1}, 
        bool fixed = false,
        bool active = false
    )
        : position(pos), text(text), id(id), color(color), isFixed(fixed) {}
};

#endif