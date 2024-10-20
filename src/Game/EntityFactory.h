#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"
#include "../Global/GlobalDataType.h"
#include <glm/glm.hpp>

namespace EntityFactory
{
    Entity CreatePlayer(glm::vec2 pos);
    Entity CreateWeapon(WeaponType type, glm::vec2 spawnPos, glm::vec2 moveDir);

    Entity CreateEnemy(glm::vec2 pos, glm::vec2 moveDir, EnemyType type);

    Entity CreateItem(glm::vec2 pos, ItemType type);

    //---------------------------------------------Tile-----------------------------------------------------------------------
    Entity CreateTile(glm::vec2 size, glm::vec2 srcRect, glm::vec2 transform, float rot, glm::vec2 boxSize);

    //---------------------------------------------Game UI---------------------------------------------------------------------
    Entity CreateInventorySlotUI(glm::vec2 pos);
    Entity CreateInventoryItemUI(glm::vec2 pos, ItemType type, int idx);

    Entity CreateHealthUI(glm::vec2 pos);
}

#endif