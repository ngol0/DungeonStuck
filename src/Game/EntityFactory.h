#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"
#include <glm/glm.hpp>

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos, glm::vec2 scale = glm::vec2(1.f), float rot = 0.f);
    Entity CreateEnemy(glm::vec2 pos, float speed, float health, glm::vec2 scale = glm::vec2(1.f), float rot = 0.f);
}

#endif