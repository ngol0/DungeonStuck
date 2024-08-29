#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <utility>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "../Global/Interface.h"
#include "../Global/WeaponData.h"

struct CollisionData : public IData
{
    std::pair<int, int> collisionPair;
    SDL_Rect overlap;
    float dt;

    virtual ~CollisionData() = default;
    CollisionData(std::pair<int,int> pair, SDL_Rect rect, float d) : collisionPair(pair), overlap(rect), dt(d) {}
};

struct AttackData : public IData
{
    glm::vec2 position;
    WeaponType weaponType;

    virtual ~AttackData() = default;
    AttackData(glm::vec2 pos, WeaponType type) : position(pos), weaponType(type) {}
};

#endif