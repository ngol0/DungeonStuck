#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"
#include <glm/glm.hpp>

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos);
    Entity CreateEnemy(glm::vec2 pos, float speed, float health, glm::vec2 scale = glm::vec2(1.f), float rot = 0.f);

    //---------------------------------------------Tile-----------------------------------------------------------------------
    Entity CreateTile(glm::vec2 size, glm::vec2 srcRect, glm::vec2 transform, float rot, glm::vec2 scale);
}

#endif