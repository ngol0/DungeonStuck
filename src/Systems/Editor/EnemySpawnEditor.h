#ifndef ENEMYSPAWNEDITOR_H
#define ENEMYSPAWNEDITOR_H

#include "../../ECS/ECS.h"

class EnemySpawnEditor : public System
{
public:
    EnemySpawnEditor() {}

    void Render(SDL_Renderer *renderer) override;
};

#endif